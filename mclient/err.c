/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include <unistd.h>
#include <err.h>

void	err_on_socket(int socket, int eval, const char *fmt)
{
  close(socket);
  err(eval, "%s", fmt);
}

