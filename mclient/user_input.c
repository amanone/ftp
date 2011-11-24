/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <sys/socket.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "client.h"

static	void	epur_intput_baduser(char *buffer, ssize_t max)
{
  char		new[BUFFER_SIZE];
  int		i;
  int		y;

  i = 0;
  y = 0;
  memset(new, '\0', BUFFER_SIZE);
  while ((buffer[i] == ' ' || buffer[i] == '\t'))
    ++i;
  while (i < max)
  {
    new[y] = buffer[i];
    ++y;
    ++i;
  }
  memset(buffer, '\0', BUFFER_SIZE);
  strcpy(buffer, new);
}

void		handle_user_input(t_client *client,
				  int *error,
       		                  char *buffer,
       		                  char *out)
{
  ssize_t	len;

  *error = 0;
  if ((len = read(0, buffer, BUFFER_SIZE)) <= 0)
  {
    if (len == 0)
      *error = WANT_QUIT;
    else
      *error = ERROR_READ_FATAL;
    return ;
  }
  epur_intput_baduser(buffer, len);
  buffer[len - 1] = '\0';
  if (len > 1)
  {
    if (get_ftp_command(client, buffer, out) != LOCAL)
      write(client->sock, out, strlen(out));
  }
  else
    printf(PROMPT);
}
