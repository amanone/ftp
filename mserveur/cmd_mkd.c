/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <unistd.h>
#include <string.h>

#include "server.h"

int		mkd_command(t_client *client)
{
  if (client->arg == NULL)
  {
    write(client->sock, BAD_ARG_MKD, strlen(BAD_ARG_MKD));
    return (1);
  }
  if (mkdir(client->arg, 0755) == -1)
  {
    write(client->sock, FAIL_MKD, strlen(FAIL_MKD));
    return (1);
  }
  else
    write(client->sock, SUCCESS_MKD, strlen(SUCCESS_MKD));
  return (0);
}

