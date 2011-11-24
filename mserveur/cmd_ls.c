/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <dirent.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "server.h"

static int    sort_dir(const struct dirent **a,
        	       const struct dirent **b)
{
  return (strcasecmp((*a)->d_name, (*b)->d_name));
}

void		finish_list(struct dirent **diren_list,
			    char *p,
			    t_client *client)
{
  free(diren_list);
  free(p);
  close (client->data_connected);
  client->data_connected = 0;
  write(client->sock, END_DATA_LS, strlen(END_DATA_LS));
}

int		loop_list(int n,
			  struct dirent **diren_list,
			  char *p,
			  t_client *client)
{
  char          buffer[BUFFER_SIZE];
  int		i;

  i = 0;
  while (i < n)
  {
    memset(buffer, 0, BUFFER_SIZE);
    if (diren_list[i]->d_name[0] != '.')
    {
      stat_file(buffer, diren_list[i]->d_name, p, client);
      write(client->data_connected, buffer, strlen(buffer));
    }
    free(diren_list[i]);
    ++i;
  }
  return (0);
}

static int		connect_pasv(t_client *client)
{
  struct sockaddr_in	clientsin;

  if (client->mode_trans == 'P')
  {
    if ((client->data_connected = accept(client->data_connected,
            (struct sockaddr *)&clientsin,
            (socklen_t[]){sizeof(clientsin)})) == -1)
    {
      write(client->sock, LIST_ERROR, strlen(LIST_ERROR));
      return (1);
    }
  }
  return (0);
}

int			list_command(t_client *client)
{
  struct dirent		**diren_list;
  int          		 n;
  char			*p;

  if (connect_pasv(client) == 1)
    return (1);
  write(client->sock, LIST_BEGIN, strlen(LIST_BEGIN));
  if ((p = get_current_dir_name()) == NULL)
  {
    write(client->sock, LIST_ERROR_M, strlen(LIST_ERROR_M));
    close(client->data_connected);
    return (1);
  }
  if ((n = scandir(p, &diren_list, 0, &sort_dir)) == -1)
  {

    write(client->sock, LIST_ERROR_M, strlen(LIST_ERROR_M));
    close(client->data_connected);
    free(p);
    return (1);
  }
  loop_list(n, diren_list, p, client);
  finish_list(diren_list, p, client);
  return (0);
}
