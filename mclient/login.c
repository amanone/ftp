/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Fri Apr  6 22:51:40 2012 thomas coudray
*/

#include <err.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client.h"

static int	send_new_user_login(char *buffer, int sock)
{
  char		out[BUFFER_OUT];

  memset(out, '\0', BUFFER_OUT);
  if (!strncmp("220", buffer, 3))
  {
    printf("Name : ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
      err_on_socket(sock, EXIT_FAILURE, "fgets()");
    sprintf(out, "USER %s\r\n", buffer);
    write(sock, out, strlen(out));
  }
  return (0);
}

static int	send_new_user_passwd(char *buffer, int sock)
{
  char		out[BUFFER_OUT];

  memset(out, '\0', BUFFER_OUT);
  if (!strncmp("331", buffer, 3))
  {
    printf("Password : ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
      err_on_socket(sock, EXIT_FAILURE, "fgets()");
    sprintf(out, "PASS %s\r\n", buffer);
    write(sock, out, strlen(out));
  }
  return (0);
}

static int	read_server_cmd(char *buffer, int sock)
{
  ssize_t	len;

  if ((len = read(sock, buffer, BUFFER_SIZE)) <= 0)
    err_on_socket(sock, EXIT_FAILURE, "read()");
  buffer[len > 2 ? len - 2 : len] = '\0';
  printf("%s\n", buffer);
  return (0);
}

static int	send_new_user_passwd_secure(char *buffer, int sock)
{
  char		out[BUFFER_OUT];
  char		*crypted;

  memset(out, '\0', BUFFER_OUT);
  if (!strncmp("331", buffer, 3))
  {
    printf("Password (secure) : ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
      err_on_socket(sock, EXIT_FAILURE, "fgets()");
    buffer[strlen(buffer) - 1] = 0;
    crypted = crypt(buffer, "E3");
    sprintf(out, "PASS %s\r\n", crypted);
    write(sock, out, strlen(out));
  }
  return (0);
}

int		handle_login(int sock)
{
  char		buffer[BUFFER_SIZE];

  setbuf(stdout, NULL);
  read_server_cmd(buffer, sock);
  send_new_user_login(buffer, sock);
  read_server_cmd(buffer, sock);
  if (g_secure == 1)
    send_new_user_passwd_secure(buffer, sock);
  else
    send_new_user_passwd(buffer, sock);
  return (0);
}
