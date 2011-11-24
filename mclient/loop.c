/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"

static void		init_data(t_client *cli, char *buf, char *out, int fd)

{
  memset(cli, -1, sizeof(*cli));
  memset(out, '\0', BUFFER_OUT);
  memset(buf, '\0', BUFFER_SIZE);
  cli->sock = fd;
  cli->recv_here = STDOUT_FILENO;
  cli->quit = OFF;
  cli->mode = ASCII_MODE;
  cli->type = ACTIF;
  cli->nbrecv = 0;
}

static	int		select_max_fd(t_client *client, int fd)
{
  int			nfds;

  nfds = MAX(client->control, STDIN_FILENO);
  nfds = MAX(client->control, nfds);
  nfds = MAX(client->data, nfds);
  nfds = MAX(client->recv_here, nfds);
  nfds = MAX(client->send_file, nfds);
  nfds = MAX(fd, nfds);
  return (++nfds);
}

static void		init_select(fd_set *rfds, const t_client *cli, int fd)
{
  FD_ZERO(rfds);
  FD_SET(STDIN_FILENO, rfds);
  FD_SET(fd, rfds);
  if (IS_ACTIVE(cli->data))
    FD_SET(cli->data, rfds);
  if (IS_ACTIVE(cli->control))
    FD_SET(cli->control, rfds);
}

static int		exiting(int error)
{

  if (error == WANT_QUIT)
    printf(QUIT_USER);
  else
    fprintf(stderr, "An unexpected error occured (%d) %s\n",
        error,
        IS_PERRABLE(error) ? strerror(errno) : "");
  return (error);
}

int			loop(int fd, int *error)
{
  char			buffer[BUFFER_SIZE];
  char			out[BUFFER_OUT];
  fd_set		readfds;
  t_client		cli;

  init_data(&cli, buffer, out, fd);
  while (1)
  {
    init_select(&readfds, &cli, fd);
    if (select(select_max_fd(&cli, fd), &readfds, 0, 0, 0) != -1)
    {
      if (FD_ISSET(STDIN_FILENO, &readfds))
        handle_user_input(&cli, error, buffer, out);
      else if (FD_ISSET(cli.sock, &readfds))
        handle_recv_reply(&cli, error, buffer);
      else if (IS_ACTIVE(cli.data) && FD_ISSET(cli.data, &readfds))
        handle_accept_data(&cli, error);
      else if (IS_ACTIVE(cli.control) && FD_ISSET(cli.control, &readfds))
        handle_recv_data(&cli, error, buffer);
      if (*error)
        return (exiting(*error));
    }
    else
      return (fprintf(stderr, "select error: %s\n", strerror(errno)));
  }
}
