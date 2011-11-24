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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "server.h"

int		rnfr_command(t_client *client)
{
  if (client->arg != NULL)
  {
    client->tmpfile = strdup(client->arg);
    write(client->sock, SUCCESS_RENAME, strlen(SUCCESS_RENAME));
    client->flags_rename = 1;
    return (0);
  }
  write(client->sock, BAD_ARG_RN, strlen(BAD_ARG_RN));
  return (0);
}

int		rnto_command(t_client *client)
{
  if (client->arg != NULL)
  {
    rename(client->tmpfile, client->arg);
    client->flags_rename = 0;
    free(client->tmpfile);
    client->tmpfile = NULL;
    write(client->sock, SUCCESS_RENAME, strlen(SUCCESS_RENAME));
    return (0);
  }
  write(client->sock, FAIL_RN, strlen(FAIL_RN));
  return (1);
}
