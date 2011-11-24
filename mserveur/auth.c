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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

static int	cmd_auth(t_client *client)
{
  if (client->auth == 1)
    return (0);
  if (strcasecmp(client->cmd, "PASS") &&
      strcasecmp(client->cmd, "USER"))
  {
    write(client->sock, NOT_AUTH, strlen(NOT_AUTH));
    return (1);
  }
  if (client->arg == NULL)
  {
    write(client->sock, NOT_AUTH, strlen(NOT_AUTH));
    return (1);
  }
  return (2);
}

static int	find_home(t_client *client, t_user *user)
{
  client->home = strdup(user->root);
  if (chdir(client->home) != -1)
    client->masterdir = client->home;
  return (0);
}

int		get_pass(char *in,
		  	 char *realpass,
		  	 t_client *client,
                         t_user *user)
{
  char		*p;

  if ((p = crypt(realpass, "E3")) == NULL)
    return (write(client->sock, CRYPT_FAIL, strlen(CRYPT_FAIL)));
  if (!strcmp(p, in))
    return (find_home(client, user));
  return (write(client->sock, LOGIN_FAIL, strlen(LOGIN_FAIL)));
}

int		authenticator(t_client *client)
{
  t_user	*user;

  if (cmd_auth(client) != 2)
    return (cmd_auth(client));
  if (client->has_login == 1)
  {
    if (!strcasecmp(client->cmd, "PASS"))
    {
      SLIST_FOREACH(user, &client->list, next)
        if (!strcasecmp(client->login, user->user))
        {
          if (g_opt.flags & opt_secure)
            return (get_pass(client->arg, user->pass, client, user));
          else if (!strcmp(client->arg, user->pass))
            return (find_home(client, user));
        }
    }
    return (write(client->sock, LOGIN_FAIL, strlen(LOGIN_FAIL)));
  }
  else
  {
    if (strcasecmp(client->cmd, "USER") == 0)
      return (0);
    return (write(client->sock, LOGIN_FAIL, strlen(LOGIN_FAIL)));
  }
}
