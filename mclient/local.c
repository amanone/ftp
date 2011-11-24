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
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "client.h"

int		lcd_command(char *arg)
{
  if (arg == NULL)
    printf("lcd need argument\n");
  else
  {
    if (chdir(arg) == -1)
      perror("cd :");
  }
  printf(PROMPT);
  return (LOCAL);
}

int		lpwd_command(char *arg)
{
  char		*pwd;

  (void) arg;
  if ((pwd = get_current_dir_name()) != NULL)
  {
    printf("[LOCAL]: %s\n", pwd);
    free(pwd);
    printf(PROMPT);
  }
  return (LOCAL);
}

int		lrm_command(char *arg)
{
  if (arg == NULL)
    printf("lrm need argument\n");
  else
  {
    if (unlink(arg) == -1)
      perror("rm :");
  }
  printf(PROMPT);
  return (LOCAL);
}

int		lrmdir_command(char *arg)
{
  if (arg == NULL)
    printf("lrmdir need argument\n");
  else
  {
    if (rmdir(arg) == -1)
      perror("rmdir :");
  }
  printf(PROMPT);
  return (LOCAL);
}

int		lmkdir_command(char *arg)
{
  if (arg == NULL)
    printf("lmkdir need argument\n");
  else
  {
    if (mkdir(arg, 0755) == -1)
      perror("lmkdir :");
  }
  printf(PROMPT);
  return (LOCAL);
}
