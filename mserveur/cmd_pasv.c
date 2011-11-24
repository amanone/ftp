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
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

void			share_port(t_client *client)
{
  struct sockaddr_in	sin;
  char			*ip;
  char			buffer[BUFFER_SIZE];
  int			port_data;
  int			sock;

  port_data = 1220;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    err(EXIT_FAILURE, "socket()");
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port_data);
  sin.sin_family = AF_INET;
  while (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    sin.sin_port = htons(++port_data);
  if (listen(sock, 1) < 0)
    err_on_socket(sock, EXIT_FAILURE, "listen()");
  if (getsockname(client->sock, (struct sockaddr *)&sin,
        (socklen_t[]){sizeof(struct sockaddr_in)}) == -1)
    err_on_socket(client->sock, EXIT_FAILURE, "getsockname()");
  ip = (char *)&sin.sin_addr;
  sprintf(buffer, "227 %d,%d,%d,%d,%d,%d\r\n", UC(ip[0]), UC(ip[1]),
      UC(ip[2]), UC(ip[3]),
      (port_data >> 8) & 0xFF, port_data & 0xFF);
  write(client->sock, buffer, strlen(buffer));
  client->data_connected = sock;
}

int		pasv_command(t_client *client)
{
  share_port(client);
  client->mode_trans = 'P';
  return (0);
}
