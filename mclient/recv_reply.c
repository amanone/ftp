/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <sys/socket.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "client.h"

void	handle_close_data_connection(t_client *cli, char *buffer)
{
  if (!strncmp("226", buffer, 3))
  {
    if (cli->control > 0)
      close(cli->control);
    cli->control = -1;

    if (cli->recv_here > 1)
    {
      close(cli->recv_here);
      cli->recv_here = 1;
    }
    cli->nbrecv = 0;
  }
}

void	print_recv_reply(ssize_t len, char *buffer)
{
  buffer[len - 1] = '\0';
  printf("\r%s\n", buffer);
}

void		handle_recv_reply(t_client *cli,
				  int *error,
				  char *buffer)
{
  ssize_t	len;

  *error = 0;
  if ((len = read(cli->sock, buffer, BUFFER_SIZE)) <= 0)
  {
    if (len == 0)
    {
      if (cli->quit == ON)
        *error = WANT_QUIT;
      else
      {
      printf(QUIT_SERVER);
      *error = ERROR_EOF_RECV;
      }
    }
    else
      *error = ERROR_READ_FATAL;
    return ;
  }
  print_recv_reply(len, buffer);
  handle_close_data_connection(cli, buffer);
  if (cli->recv_here == STDOUT_FILENO)
    printf(PROMPT);
}
