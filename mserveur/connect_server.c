/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include	<arpa/inet.h>
#include	<assert.h>
#include	<err.h>
#include	<netinet/in.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/socket.h>
#include	<sys/socket.h>
#include	<sys/types.h>
#include	<unistd.h>

#include	"server.h"

static void		daemon_option(int *error)
{
  *error = 0;
  if (g_opt.flags & opt_daemonize)
  {
    printf("Daemonize...\n");
      if (daemon(1, 0) == -1)
        perror("daemon()");
  }
}

int			loop_accept(t_listhead list,
				   int sock,
				   struct sockaddr_in *sin)
{
  int			error;
  int			fd;
  pid_t			pid;
  pid_t			pidmaster;

  daemon_option(&error);
  while (!error)
  {
    if ((fd = accept(sock, (struct sockaddr *)sin,
            (socklen_t[]){sizeof(*sin)})) != -1)
    {
      pidmaster = getpid();
      if ((pid = fork()) == -1)
        perror("fork()");
      else if (!pid)
      {
        close(sock);
        run_life_son(fd, pidmaster, sin, list);
      }
      else
        close(fd);
    }
  }
  close(sock);
  return (error);
}

int			connect_server(t_listhead list, int port)
{
  int			sock;
  struct sockaddr_in	sin;
  struct protoent	*prot;
  int			domain;

  printf("use port %d\n", port);
  if ((prot = getprotobyname("TCP")) == NULL)
    err(EXIT_FAILURE, "getprotobyname()");
  domain = ((g_opt.flags & opt_ipv6) ? AF_INET6 : PF_INET);
  if ((sock = socket(domain, SOCK_STREAM, prot->p_proto)) == -1)
    err(EXIT_FAILURE, "socket()");
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
        (int[]){1}, sizeof(int)) == -1)
    err(EXIT_FAILURE, "setsockopt()");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
    err_on_socket(sock, EXIT_FAILURE, "bind()");
  if (listen(sock, SOMAXCONN) == -1)
    err_on_socket(sock, EXIT_FAILURE, "listen()");
  signal(SIGPIPE, SIG_IGN);
  return (loop_accept(list, sock, &sin));
}
