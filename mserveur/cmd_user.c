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
#include <unistd.h>

#include "server.h"

int	user_command(t_client *client)
{
  if (client->arg == NULL)
    client->login = strdup(DEFAULT_USER);
  else
    client->login = strdup(client->arg);
  client->has_login = 1;
  write(client->sock, NEED_PASS, strlen(NEED_PASS));
  return (0);
}
