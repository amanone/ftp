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
#include <assert.h>
#include <fcntl.h>

#include "server.h"

void			get_rootdir(char *buffer, t_client *client)
{
  size_t		i;
  char			*ptr;

  i = 0;
  assert(buffer != NULL);
  assert(client->masterdir != NULL);
  while (buffer[i])
  {
    if (buffer[i] == client->masterdir[i])
    {
      buffer[i] = ' ';
      ++i;
    }
    else
    {
      ptr = strtok(buffer, "\n\t ");
      client->curdir = ptr;
      return ;
    }
  }
}

int		pwd_command(t_client *client)
{
  char		buff[BUFFER_SIZE];
  char		out[BUFFER_SIZE];

  memset(buff, 0, BUFFER_SIZE);
  getcwd(buff, BUFFER_SIZE);
  if (buff == NULL)
  {
    perror("getcwd");
    write(client->sock, CODE_PWD_FAIL, strlen(CODE_PWD_FAIL));
    return (-1);
  }
  buff[strlen(buff)] = '/';
  buff[strlen(buff) + 1] = '\0';
  get_rootdir(buff, client);
  sprintf(out, "%s \"%s\"\r\n", CODE_PWD_OK, client->curdir);
  write(client->sock, out, strlen(out));
  return (0);
}
