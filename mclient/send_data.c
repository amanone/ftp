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
#include <unistd.h>

#include "client.h"

void		finish_sending_data(t_client *cli)
{
  close(cli->control);
  close(cli->send_file);
  close(cli->data);
  cli->control = -1;
  cli->send_file = -1;
  cli->data = -1;
}

/*
 ** put / stor
 */
int		handle_send_data(t_client *cli)
{
  char		buffer[BUFFER_OUT];
  ssize_t	len;

  len = 0;
  if (cli->send_file > 0)
  {
    while ((len = read(cli->send_file, buffer, BUFFER_OUT)) > 0)
      write(cli->control, buffer, len);
    if (len == -1)
    {
      perror("read()");
      return (1);
    }
    finish_sending_data(cli);
  }
  return (0);
}
