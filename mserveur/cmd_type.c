/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"

int		type_command(t_client *client)
{
  if (client->arg == NULL)
  {
    write(client->sock, BAD_PARAM_TYPE, strlen(BAD_PARAM_TYPE));
    return (-1);
  }
  if (!strcmp(client->arg, "I"))
  {
    write(client->sock, CODE_BIN_MODE, strlen(CODE_BIN_MODE));
    client->mode = BIN_MODE;
    return (0);
  }
  if (!strcmp(client->arg, "A"))
  {
    write(client->sock, CODE_ASC_MODE, strlen(CODE_ASC_MODE));
    client->mode = ASCII_MODE;
    return (0);
  }
  write(client->sock, DEFAULT_MODE, strlen(DEFAULT_MODE));
  client->mode = ASCII_MODE;
  return (0);
}
