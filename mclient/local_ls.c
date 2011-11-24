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
#include <sys/stat.h>
#include <err.h>
#include <dirent.h>
#include <fcntl.h>

#include "client.h"

# define MAXPATH	512

struct s_info
{
  int	f;
  char	c;
};

static const struct s_info g_info[] =
{
  {S_IRUSR, 'r'},
  {S_IWUSR, 'w'},
  {S_IXUSR, 'x'},
  {S_IRGRP, 'r'},
  {S_IWGRP, 'w'},
  {S_IXGRP, 'x'},
  {S_IROTH, 'r'},
  {S_IWOTH, 'w'},
  {S_IXOTH, 'x'}
};

static int	get_right(char *buf, mode_t p)
{
  size_t	idx;

  if ((p & 0xC000) == 0xC000)
    sprintf(buf, "s");
  else if ((p & 0xA000) == 0xA000)
    sprintf(buf, "l");
  else if ((p & 0x8000) == 0x8000)
    sprintf(buf, "-");
  else if ((p & 0x6000) == 0x6000)
    sprintf(buf, "b");
  else if ((p & 0x4000) == 0x4000)
    sprintf(buf, "d");
  else if ((p & 0x2000) == 0x2000)
    sprintf(buf, "c");
  else if ((p & 0x1000) == 0x1000)
    sprintf(buf, "p");
  else
    sprintf(buf, "u");
  idx = -1;
  while (++idx < sizeof(g_info) / sizeof(*g_info))
    printf("%c", p & g_info[idx].f ? g_info[idx].c : '-');
  return (idx + 1);
}

int		stat_file(char *buf,
			  char *name,
			  char *path)
{
  struct stat       file_stat;
  char              buf_file[MAXPATH];

  snprintf(buf_file, MAXPATH, "%s/%s", path, name);
  if (stat(buf_file, &file_stat) == -1)
    return (1);
   get_right(buf, file_stat.st_mode);
  printf("%13d ", (int)file_stat.st_size);
  printf(" [%s]\n", name);
  return (0);
}

static int    sort_dir(const struct dirent **a,
        	       const struct dirent **b)
{
  return (strcasecmp((*a)->d_name, (*b)->d_name));
}

int			lls_command(char *arg)
{
  char		         buffer[BUFFER_SIZE];
  int			i;
  struct dirent		**diren_list;
  int          		 n;
  char			*p;

  i = -1;
  (void) arg;
  if ((p = get_current_dir_name()) == NULL)
    return (LOCAL);
  if ((n = scandir(p, &diren_list, 0, &sort_dir)) == -1)
    return (LOCAL);
  printf("=====LOCAL LS====\n");
  while (++i < n)
  {
    memset(buffer, 0, BUFFER_SIZE);
    if (diren_list[i]->d_name[0] != '.')
      stat_file(buffer, diren_list[i]->d_name, p);
    free(diren_list[i]);
  }
  free(diren_list);
  free(p);
  printf(PROMPT);
  return (LOCAL);
}
