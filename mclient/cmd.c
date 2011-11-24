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
#include <stdio.h>
#include <err.h>
#include <fcntl.h>

#include "client.h"

static const struct s_cmd g_cmd[] =
{
  {"ls", "LIST", 1},
  {"lss", "NLST", 1},
  {"cd", "CWD", 0},
  {"mkdir", "MKD", 0},
  {"rmdir", "RMD", 0},
  {"rm", "DELE", 0},
  {"get", "RETR", 1},
  {"mget", "mget", 1},
  {"quit", "QUIT", 0},
  {"put", "STOR", 1}
};

# define LOCALCMD(NAME)	{#NAME, NAME ## _command}

static const struct s_local_cmd g_local[] =
{
  LOCALCMD(lcd),
  LOCALCMD(lpwd),
  LOCALCMD(lls),
  LOCALCMD(lmkdir),
  LOCALCMD(lrm),
  LOCALCMD(lhelp),
  LOCALCMD(lrmdir)
};

int			lhelp_command(char *arg)
{
  (void) arg;
  printf(" lcd   : change local directory\n");
  printf(" lpwd  : get the local working directory\n");
  printf(" lls	 : list local file\n");
  printf(" lmkdir: mkdir local directory\n");
  printf(" lrm   : remove local file\n");
  printf(" lrmdir: remove local directory\n");
  printf(" lhelp : show available local cmd\n");
  printf(PROMPT);
  return (LOCAL);
}

static void		read_data_sock(t_client *client,
				      const struct s_cmd *info,
				      const char *file)
{
  if (!strcmp(info->user, "quit"))
    client->quit = ON;
  if (info->rinfo)
  {
    if (!strcmp(info->user, "get"))
      if ((client->recv_here = open(file, O_CREAT | O_WRONLY, 0644)) == -1)
        return (warn("get fail: "));
    if (!strcmp(info->user, "put"))
      if ((client->send_file = open(file, O_RDONLY)) == -1)
        return (warn("put fail: "));
    if (client->type == ACTIF)
      share_port(client);
    else if (client->type == PASSIF)
      passif_mode(client);
  }
}

int		local_command(char *cmd, char *arg)
{
  size_t	idx;

  idx = -1;
  while (++idx < sizeof(g_local) / sizeof(*g_local))
  {
    if (!strcmp(cmd, g_local[idx].cmd))
      return (g_local[idx].func(arg));
  }
  return (0);
}

int		get_ftp_command(t_client *client, char *buffer, char *out)
{
  char		*cmd;
  char		*arg;
  size_t	idx;

  idx = -1;
  client->recv_here = STDOUT_FILENO;
  cmd  = buffer + strspn(buffer, " \t\n");
  arg = cmd + strcspn(buffer, " \t\n");
  if (*arg)
    *arg++ = 0;
  if (local_command(cmd, arg))
    return (LOCAL);
  if (!strcmp(cmd, "PORT"))
    return (port_command(client, arg));
  while (++idx < sizeof(g_cmd) / sizeof(*g_cmd))
  {
    if (!strcmp(cmd, g_cmd[idx].user))
    {
      sprintf(out, "%s %s\r\n", g_cmd[idx].ftp_cmd, (arg ? arg : ""));
      read_data_sock(client, &g_cmd[idx], arg);
      return (1);
    }
  }
  sprintf(out, "%s\r\n", buffer);
  return (0);
}
