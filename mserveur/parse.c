/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include	<err.h>
#include	<stdio.h>
#include	<assert.h>
#include	<stdlib.h>
#include	<string.h>

#include	"server.h"

int		split_arg(char *buff, t_client *client)
{
  char		*ptr;

  assert(buff != NULL);
  if ((client->long_arg = strdup(buff)) == NULL)
    return (1);
  ptr = strtok(buff, "\n\t ");
  client->cmd = ptr;
  ptr = strtok(NULL, "\n\t ");
  client->arg = ptr;
  if (client->cmd == NULL)
    return (1);
  return (0);
}

int		format_input(char *buffer, ssize_t len, t_client *client)
{
  ssize_t	idx;

  idx = 0;
  assert(buffer != NULL);
  while (idx < len && buffer[idx] != '\0')
  {
    if (buffer[idx] == '\r' || buffer[idx] == '\n')
      buffer[idx] = '\0';
    ++idx;
  }
  buffer[idx] = '\0';
  return (split_arg(buffer, client));
}
