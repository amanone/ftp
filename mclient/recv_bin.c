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
** BIN MODE:
** see rfc5198.txt appendix B. & rfc698.txt
*/
void		bin_mode(char *buffer, ssize_t len, t_client *cli)
{
  if (write(cli->recv_here, buffer, len) == -1)
    perror("write() binary_mode :");
  cli->nbrecv += len;
  printf("%zd bytes\r", cli->nbrecv);
}
