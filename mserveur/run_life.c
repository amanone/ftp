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
#include	<stdlib.h>
#include	<string.h>
#include	<arpa/inet.h>

#include	"server.h"

void			init_client_struct(t_client *client,
					   pid_t pidmaster,
					   int fd,
                                           t_listhead list)
{
  memset(client, 0, sizeof(*client));
  client->arg = NULL;
  client->bell_end = 0;
  client->cmd = NULL;
  client->has_login = 0;
  client->home = NULL;
  client->list = list;
  client->long_arg = NULL;
  client->mode = ASCII_MODE;
  client->mode_trans = 'A';
  client->mpid = getpid();
  client->opt = 0;
  client->pidmaster = pidmaster;
  client->run = ON;
  client->sock = fd;
  client->to_free = NULL;
  client->masterdir = get_current_dir_name();
  if (client->masterdir == NULL)
    err(1, "get_current_dir_name ()");
}

int			loop_life_client(t_client *client)
{
  ssize_t		len;
  int			run;
  char			buff[BUFFER_SIZE];

  run = 0;
  write(client->sock, CONNECTING, strlen(CONNECTING));
  memset(buff, 0, sizeof(buff));
  while ((len = read(client->sock, buff, sizeof(buff))) > 0)
  {
    if (g_opt.flags & opt_verbose)
      printf("recve :[%s]\n", buff);
    if (!format_input(buff, len, client))
      handle_cmd(client);
    free(client->long_arg);
    memset(buff, '\0', BUFFER_SIZE);
    if (client->run == OFF)
      return (0);
  }
  return (len);
}

void			free_son(t_client *client)
{
  t_user		*user;

  free(client->masterdir);
  free(client->login);
  SLIST_FOREACH(user, &client->list, next)
  {
    free(user->user);
    free(user->pass);
    free(user->root);
  }
}

int			run_life_son(int s,
				     pid_t pid,
				     struct sockaddr_in *sin,
				     t_listhead list)
{
  int			error;
  t_client		client;

  error = 0;
  setpgid(0, pid);
  init_client_struct(&client, pid, s, list);
  printf("New client\t: %s port : %d\n",
      inet_ntoa(sin->sin_addr),
      htons(sin->sin_port));
  error = loop_life_client(&client);
  free_son(&client);
  printf("Quit client\t: %s port : %d  %s [code %d]\n",
      inet_ntoa(sin->sin_addr),
      htons(sin->sin_port),
      ((error) ? "Unexpected error occured" : "Success"),
      error);
  close(s);
  exit(error);
  return (error);
}
