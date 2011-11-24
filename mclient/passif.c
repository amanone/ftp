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
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"

void		passif_mode(t_client *client)
{
  write(client->sock, PASV_MODE, strlen(PASV_MODE));
}

int			handle_data_connection(t_client *client,
					       int port,
					       char *ip)
{
  int			sock;
  struct sockaddr_in	sin;
  struct protoent	*prot;

  if ((prot = getprotobyname("TCP")) == NULL)
    err(EXIT_FAILURE, "getprotobyname()");
  if ((sock = socket(AF_INET, SOCK_STREAM, prot->p_proto)) == -1)
    err(EXIT_FAILURE, "socket()");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(sock, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == -1)
  {
    perror("connect PORT");
    return (1);
  }
  client->data = sock;
  return (0);
}

int		get_port_and_connect_to_it(t_client *client, int idx, char *arg)
{
  char		ip[16];
  char		*ptr;
  int		port;
  int		porth;

  port = 0;
  arg[idx] = '\0';
  strncpy(ip, arg, 16);
  porth = atoi(arg + idx + 1) * 256;
  ptr = strtok(arg + idx + 1, ",");
  ptr = strtok(NULL, ",");
  if (ptr != NULL)
    port = porth + atoi(ptr);
  if (handle_data_connection(client, port, ip) != 0)
    printf("port fail\n");
  else
    printf("port ok\n");
  return (0);
}

int		port_command(t_client *client, char *arg)
{
  int		idx;
  int		count;

  idx = 0;
  count = 0;
  if (arg == NULL)
  {
    printf("pas d'argument\n");
    return (0);
  }
  while (arg[idx] != '\0')
  {
    if (arg[idx] == ',')
    {
      arg[idx] = '.';
      ++count;
    }
    if (count == 4)
      return (get_port_and_connect_to_it(client, idx, arg));
    ++idx;
  }
  return (0);
}
