/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>

#include	"server.h"

void		usage(const char *bin)
{
  printf("[usage]: %s [port = 4242]\n", bin);
  printf("-d: daemonize the server\n");
  printf("-f [file]: use specific authentication file\n");
  printf("-v: make server verbose\n");
  printf("-h: show help cmdline\n");
  printf("-i: swith to ipv6 mode\n");
  exit(EXIT_SUCCESS);
}

void		handle_option(int argc, char * const argv[])
{
  char		c;

  g_opt.flags = 0;
  g_opt.file = NULL;
  while ((c = getopt(argc, argv, "sidhf:v")) != -1)
  {
    if (c == 'd')
      g_opt.flags |= opt_daemonize;
    if (c == 'h')
      usage(argv[0]);
    if (c == 'f')
    {
      g_opt.flags |= opt_config_file;
      g_opt.file = optarg;
    }
    if (c == 'v')
      g_opt.flags |= opt_verbose;
    if (c == 'i')
      g_opt.flags |= opt_ipv6;
    if (c == 's')
      g_opt.flags |= opt_secure;
  }
}

int		main(int argc, char * const argv[])
{
  t_listhead	list;
  int		errcode;

  handle_option(argc, argv);
  list = handle_config();
  errcode = connect_server(list, argc > 1 ? atoi(argv[1]) : 4242);
  return (errcode);
}
