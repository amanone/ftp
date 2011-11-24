/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <arpa/inet.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

int			handle_data_connection(t_client *client,
					       int port,
					       char *ip)
{
  int			sock;
  struct sockaddr_in	sin;
  struct protoent	*prot;
  int			domain;

  if ((prot = getprotobyname("TCP")) == NULL)
    err(EXIT_FAILURE, "getprotobyname()");
  domain = ((g_opt.flags & opt_ipv6) ? AF_INET6 : PF_INET);
  if ((sock = socket(domain, SOCK_STREAM, prot->p_proto)) == -1)
    err(EXIT_FAILURE, "socket()");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == -1)
  {
    perror("connect PORT");
    return (1);
  }
  client->data_connected = sock;
  return (0);
}

int		get_port_and_connect_to_it(t_client *client, int idx)
{
  char		ip[16];
  char		*ptr;
  int		port;
  int		porth;

  port = 0;
  client->arg[idx] = '\0';
  strncpy(ip, client->arg, 16);
  porth = atoi(client->arg + idx + 1) * 256;
  ptr = strtok(client->arg + idx + 1, ",");
  ptr = strtok(NULL, ",");
  if (ptr != NULL)
    port = porth + atoi(ptr);
  if (handle_data_connection(client, port, ip) != 0)
    write(client->sock, PORT_FAIL, strlen(PORT_FAIL));
  else
    write(client->sock, PORT_OK, strlen(PORT_OK));
  return (0);
}

int		port_command(t_client *client)
{
  int		idx;
  int		count;

  idx = 0;
  count = 0;
  if (client->arg == NULL)
  {
    write(client->sock, CODE_PORT_NO_ARG, strlen(CODE_PORT_NO_ARG));
    return (0);
  }
  client->mode_trans = 'A';
  while (client->arg[idx] != '\0')
  {
    if (client->arg[idx] == ',')
    {
      client->arg[idx] = '.';
      ++count;
    }
    if (count == 4)
      return (get_port_and_connect_to_it(client, idx));
    ++idx;
  }
  return (0);
}
