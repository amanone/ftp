/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "server.h"

# define BELLL	("\a\r")

static void	finish_retr(t_client *client, int file)
{
  write(client->sock, END_DATA_RETR, strlen(END_DATA_RETR));
  close(file);
  close(client->data_connected);
  if (client->bell_end == 1)
    write(client->sock, BELLL, strlen(BELLL));
  client->data_connected = 0;
}

static int	retr_ascii(t_client *client, int file)
{
  char		buffer[BUFFER_OUT];
  ssize_t	len;

  write(client->sock, RETR_BEGIN_A, strlen(RETR_BEGIN_A));
  while ((len = read(file, buffer, BUFFER_OUT)) > 0)
    write(client->data_connected, buffer, len);
  return (0);
}

static int	retr_bin(t_client *client, int file)
{
  char		buffer[BUFFER_OUT];
  ssize_t	len;

  write(client->sock, RETR_BEGIN_B, strlen(RETR_BEGIN_B));
  while ((len = read(file, buffer, BUFFER_OUT)) > 0)
    write(client->data_connected, buffer, len);
  return (0);
}

static int		connect_pasv(t_client *client)
{
  struct sockaddr_in	clientsin;

  if (client->mode_trans == 'P')
  {
    if ((client->data_connected = accept(client->data_connected,
            (struct sockaddr *)&clientsin,
            (socklen_t[]){sizeof(clientsin)})) == -1)
    {
    write(client->sock, ERROR_RETR_OPEN, strlen(ERROR_RETR_OPEN));
      return (1);
    }
  }
  return (0);
}
int		retr_command(t_client *client)
{
  int		file;

  if (connect_pasv(client) == 1)
    return (1);
  if (client->arg == NULL)
  {
    write(client->sock, USAGE_GET, strlen(USAGE_GET));
    close(client->data_connected);
    return (1);
  }
  if ((file = open(client->arg, O_RDONLY)) == -1)
  {
    write(client->sock, ERROR_RETR_OPEN, strlen(ERROR_RETR_OPEN));
    close(client->data_connected);
    return (1);
  }
  if (client->mode == ASCII_MODE)
    retr_ascii(client, file);
  else if (client->mode == BIN_MODE)
    retr_bin(client, file);
  finish_retr(client, file);
  return (0);
}
