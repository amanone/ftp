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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

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
    sprintf(buf + idx + 1, "%c", p & g_info[idx].f ? g_info[idx].c : '-');
  return (idx + 1);
}

void		   fill_buff(struct stat file_stat,
      			    char *buf,
      			    size_t idx,
      			    char *file)
{
  idx += snprintf(buf + idx, 6, "%5d", (int)file_stat.st_nlink);
  idx += snprintf(buf + idx, 7, "%5d", (int)file_stat.st_uid);
  idx += snprintf(buf + idx, 10, "%9d", (int)file_stat.st_gid);
  idx += snprintf(buf + idx, 15, "%13d ", (int)file_stat.st_size);
  snprintf(buf + idx, 13, "%s", ctime(&(file_stat.st_atime)) + 4);
  idx += 12;
  idx += snprintf(buf + idx, MAXPATH, " %s\r\n", file);
}

int		stat_file(char *buf,
			 char *name,
			 char *path,
			 t_client *client)
{
  struct stat       file_stat;
  size_t	    pos;
  char              buf_file[MAXPATH];

  (void) client;
  snprintf(buf_file, MAXPATH, "%s/%s", path, name);
  if (stat(buf_file, &file_stat) == -1)
    return (1);
  pos = get_right(buf, file_stat.st_mode);
  fill_buff(file_stat, buf, pos, name);
  return (0);
}
