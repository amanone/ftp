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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"

static int		usage(const char *nameb)
{
  fprintf(stderr, "Usage : %s [hostname ip][port=21]\n", nameb);
  return (EXIT_FAILURE);
}

static int		connect_server(const char *addr, int port)
{
  int			sok;
  int			error;
  struct hostent	*host;
  struct protoent	*prot;
  struct sockaddr_in	sin;

  error = 0;
  if ((prot = getprotobyname("TCP")) == NULL)
    err(EXIT_FAILURE, "getprotobyname()");
  if ((sok = socket(AF_INET, SOCK_STREAM, prot->p_proto)) == -1)
    err(EXIT_FAILURE, "socket()");
  if (setsockopt(sok, SOL_SOCKET, SO_REUSEADDR, (int[]){1}, sizeof(int)) == -1)
    err(EXIT_FAILURE, "setsockopt()");
  if ((host = gethostbyname(addr)) == NULL)
    err_on_socket(sok, EXIT_FAILURE, "gethostbyname()");
  memcpy(&sin.sin_addr.s_addr, host->h_addr, host->h_length);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if ((connect(sok, (struct sockaddr *)&sin, sizeof(sin))) == -1)
    err_on_socket(sok, EXIT_FAILURE, "connect()");
  signal(SIGPIPE, SIG_IGN);
  handle_login(sok);
  return (loop(sok, &error));
}

int			main(int argc, const char *argv[])
{
  int			errcode;

  if (argc < 2)
    return (usage(argv[0]));
  if (argc > 3)
    if (!strcmp(argv[argc - 1], "--secure") || !strcmp(argv[argc - 1], "-s"))
      g_secure = 1;
  errcode = connect_server(argv[1], argc > 2 ? atoi(argv[2]) : 21);
  return (errcode);
}
