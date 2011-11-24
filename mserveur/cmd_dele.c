/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <string.h>
#include <unistd.h>

#include "server.h"

int		dele_command(t_client *client)
{
  if (client->arg == NULL)
  {
    write(client->sock, BAD_ARG_DELE, strlen(BAD_ARG_DELE));
    return (1);
  }
  if (unlink(client->arg) == -1)
  {
    write(client->sock, FAIL_DEL, strlen(FAIL_DEL));
    return (1);
  }
  else
    write(client->sock, SUCCESS_DEL, strlen(SUCCESS_DEL));
  return (0);
}

int		syst_command(t_client *client)
{
  write(client->sock, SYS_INFO, strlen(SYS_INFO));
  return (0);
}
