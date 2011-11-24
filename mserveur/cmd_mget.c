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

int		bell_command(t_client *client)
{
  client->bell_end = 1;
  write(client->sock, "500 BELL OK :D", strlen("500 BELL OK :D"));
  return (1);
}

static void	finish_retr(t_client *client, int file)
{
  write(client->sock, END_DATA_RETR, strlen(END_DATA_RETR));
  close(file);
  close(client->data_connected);
  client->data_connected = 0;
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

int		get_each(char *dfile, t_client *client)
{
  int		file;

  if ((file = open(dfile, O_RDONLY)) == -1)
  {
    write(client->sock, ERROR_RETR_OPEN, strlen(ERROR_RETR_OPEN));
    close(client->data_connected);
    return (1);
  }
  retr_bin(client, file);
  finish_retr(client, file);
  return (0);
}

int		mget_command(t_client *client)
{
  char		*ptr;

  if (client->arg == NULL)
  {
    write(client->sock, USAGE_GET, strlen(USAGE_GET));
    close(client->data_connected);
    return (1);
  }
  return (1);
  if ((ptr = strtok(client->long_arg, " \t\n")) != NULL)
    get_each(ptr, client);

  while ((ptr = strtok(NULL, " \t\n")) != NULL)
    get_each(ptr, client);
  return (0);
}
