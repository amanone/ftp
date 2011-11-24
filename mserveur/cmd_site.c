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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "server.h"

int		chmod_command(t_client *client)
{
  char		buf[BUFFER_OUT];
  char		*ptr;
  char		*perm;
  char		*file;

  strcpy(buf, client->long_arg);
  ptr = strtok(buf, "\n\t ");
  if ((ptr = strtok(NULL, "\n\t ")) == NULL)
    return (1);
  if (!strcasecmp("chmod", ptr))
  {
    if ((perm = strtok(NULL, "\n\t ")) == NULL)
      return (1);
    if ((file = strtok(NULL, "\n\t ")) == NULL)
      return (1);
    if (chmod(file, strtol(perm, NULL, 8)) == -1)
      return (1);
    return (0);
  }
  return (1);
}

int		site_command(t_client *client)
{
  if (!chmod_command(client))
  {
    write(client->sock, SUCCESS_CHMOD, strlen(SUCCESS_CHMOD));
    return (0);
  }
  return (1);
}
