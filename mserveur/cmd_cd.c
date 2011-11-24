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

#include "server.h"

/*
** Idiot, idiot. ca aurait ete *vraiment* mieux d'utiliser
** un vrai chroot daemon(3), launchd(3), ou la libdaemon...
*/
static int		do_root_change(const t_client *client)
{
  char			out[BUFFER_SIZE];

  sprintf(out, "%s%s", client->masterdir, client->arg);
  if (chdir(out) == -1)
  {
    write(client->sock, CODE_CD_FAIL, strlen(CODE_CD_FAIL));
    return (1);
  }
  write(client->sock, CODE_CD_OK, strlen(CODE_CD_OK));
  return (0);
}

static int		handle_up_cwd(const t_client *client)
{
  char			*p;

  if ((p = get_current_dir_name()) == NULL)
    return (1);
  if (strcmp(p, client->masterdir))
  {
    if (chdir("..") == -1)
      perror("chdir");
    free(p);
    return (0);
  }
  free(p);
  return (1);
}

int			cwd_command(t_client *client)
{
  if (client->arg == NULL)
  {
    if (chdir(client->masterdir) == -1)
    {
      write(client->sock, CODE_CD_FAIL_HOME, strlen(CODE_CD_FAIL_HOME));
      return (1);
    }
    write(client->sock, CODE_CD_OK_HOME, strlen(CODE_CD_OK_HOME));
    return (0);
  }
  if (client->arg[0] == '/')
    return (do_root_change(client));
  else if (!strncmp(client->arg, "..", 2))
    handle_up_cwd(client);
  else if (chdir(client->arg) == -1)
  {
    write(client->sock, CODE_CD_FAIL, strlen(CODE_CD_FAIL));
    return (1);
  }
  write(client->sock, CODE_CD_OK, strlen(CODE_CD_OK));
  return (0);
}

int			cdup_command(t_client *client)
{
  if (!handle_up_cwd(client))
  {
    write(client->sock, CODE_CD_OK, strlen(CODE_CD_OK));
    return (0);
  }
  else
    write(client->sock, CODE_CD_FAIL, strlen(CODE_CD_FAIL));
  return (1);
}
