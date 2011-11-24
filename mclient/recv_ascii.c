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

/*
** ASCII MODE:
** see rfc5198.txt appendix B. & rfc698.txt
*/
void		ascii_mode(char *buffer, ssize_t len, t_client *cli)
{
  char		tmp[BUFFER_SIZE];
  int		i;
  int		y;

  i = 0;
  y = 0;
  memset(tmp, '\0', BUFFER_SIZE);
  while (i < len)
  {
    if (buffer[i] == '\r' && buffer[i + 1] == '\n')
      i++;
    else
      tmp[y++] = buffer[i++];
  }
  memset(buffer, '\0', BUFFER_SIZE);
  if (write(cli->recv_here, tmp, y) == -1)
    perror("write() ascii_mode :");
  cli->nbrecv += y;
  printf("%zd bytes\r", cli->nbrecv);
}

