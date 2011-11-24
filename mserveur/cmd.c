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

static const struct s_cmd g_cmd[] =
{
  COMMAND(bell),
  COMMAND(bin),
  COMMAND(cdup),
  COMMAND(chmod),
  COMMAND(cwd),
  COMMAND(dele),
  COMMAND(list),
  COMMAND(mget),
  COMMAND(mkd),
  COMMAND(pass),
  COMMAND(pasv),
  COMMAND(port),
  COMMAND(pwd),
  COMMAND(quit),
  COMMAND(retr),
  COMMAND(rmd),
  COMMAND(rnfr),
  COMMAND(rnto),
  COMMAND(site),
  COMMAND(stor),
  COMMAND(syst),
  COMMAND(type),
  COMMAND(user)
};

int		asc_command(t_client *client)
{
  write(client->sock, CODE_ASC_MODE, strlen(CODE_ASC_MODE));
  client->mode = ASCII_MODE;
  return (0);
}

int		bin_command(t_client *client)
{
  write(client->sock, CODE_BIN_MODE, strlen(CODE_BIN_MODE));
  client->mode = BIN_MODE;
  return (0);
}

int		handle_cmd(t_client *client)
{
  size_t	idx;
  int		ret;

  idx = 0;
  ret = -1;
  while (idx < sizeof(g_cmd) / sizeof(*g_cmd))
  {
    if (!strcasecmp(g_cmd[idx].cmd_in, client->cmd))
    {
      if (authenticator(client))
        return (-1);
      else
        return (g_cmd[idx].func(client));
    }
    ++idx;
  }
  if (ret == -1)
    write(client->sock, BAD_CMD, strlen(BAD_CMD));
  return (0);
}
