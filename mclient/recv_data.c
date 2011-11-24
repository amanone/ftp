/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "client.h"

void		handle_recv_data(t_client *cli, int *error, char *buff)
{
  ssize_t	len;

  if ((len = read(cli->control, buff, BUFFER_SIZE - 1)) <= 0)
  {
    if (len == 0)
      return ;
    else
      *error = ERROR_READ_FATAL;
    return ;
  }
  if (cli->recv_here != STDOUT_FILENO && IS_ACTIVE(cli->recv_here))
  {
    if (cli->mode == ASCII_MODE)
      ascii_mode(buff, len, cli);
    else if (cli->mode == BIN_MODE)
      bin_mode(buff, len, cli);
  }
  else
  {
    buff[len - 1] = '\0';
    printf("\r%s\n", buff);
  }
}

void			handle_accept_data(t_client *cli, int *error)
{
  struct sockaddr_in	client;

  if ((cli->control = accept(cli->data, (struct sockaddr *)&client,
          (socklen_t[]){sizeof(client)})) == -1)
  {
    close(cli->data);
    *error = ERROR_ACCEPT;
  }
  handle_send_data(cli);
}

