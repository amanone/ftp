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
#include <stdlib.h>
#include <sys/queue.h>

#include "server.h"

t_user		*handle_line(char *buff)
{
  t_user	*user;

  if ((user = malloc(sizeof(*user))) == NULL)
    return (NULL);
  if (strchr(buff, ';') != NULL)
    return (NULL);
  user->user = strtok(buff, " \t\n");
  user->pass = strtok(NULL, " \t\n");
  user->root = strtok(NULL, " \t\n");
  if (!user->user || !user->pass || !user->root)
    return (NULL);
  user->user = strdup(user->user);
  user->pass = strdup(user->pass);
  user->root = strdup(user->root);
  return (user);
}

t_listhead	handle_config(void)
{
  FILE		*file;
  char		buff[BUFFER_OUT];
  t_user	*user;
  t_listhead	head;

  SLIST_INIT(&head);
  if ((file = fopen(g_opt.file ? g_opt.file : FILE_CONFIG, "r")) == NULL)
  {
    fprintf(stderr, "Failed top open config file (%s)\n", FILE_CONFIG);
    return (head);
  }
  memset(buff, '\0', BUFFER_OUT);
  while (fgets(buff, BUFFER_OUT, file) != NULL)
    if ((user = handle_line(buff)) != NULL)
      SLIST_INSERT_HEAD(&head, user, next);
  SLIST_FOREACH(user, &head, next)
    printf("loaded user: %s %s %s\n", user->user, user->pass, user->root);
  fclose(file);
  return (head);
}

