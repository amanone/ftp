/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#ifndef CLIENT_H_

# define CLIENT_H_

# ifndef _NETDB_H
#  include <netdb.h>
# endif /* netdb.h */

# define IS_ACTIVE(x)		(x != -1 ? 1 : 0)
# define MAX(x, y)		(x > y ? x : y)
# define MIN(x, y)		(x < y ? x : y)

# define BUFFER_SIZE		(1024)
# define BUFFER_OUT		(2048)

# define ERROR_EOF_RECV		(110)
# define ERROR_ACCEPT		(120)
# define ERROR_READ_FATAL	(20)
# define WANT_QUIT		(10)
# define LOCAL			(14)

# define IS_PERRABLE(x)		(x < 100  ? 1 : 0)

# define PROMPT			("ftp>")
# define QUIT_USER		("221 Goodbye.\n")
# define QUIT_SERVER		(" Server shutdown...\n")
# define PASV_MODE		("PASV")

# define PASSIF			(121)
# define ACTIF			(531)

# define  ASCII_MODE		(0xCAFED00D)
# define  BIN_MODE		(0xCAFEBABE)

# define UC(x)  ((int)		(((int) x) & 0xFF))

# define DATA_PORT		(3615)

# define ON			(1)
# define OFF			(0)

int		g_secure;

typedef struct	s_client
{
  int		control;
  int		data;
  int		quit;
  int		type;
  int		recv_here;
  int		send_file;
  int		sock;
  ssize_t	nbrecv;
  unsigned int	mode;
}		t_client;

typedef struct	s_cmd
{
  const char	*user;
  const char	*ftp_cmd;
  int		rinfo;
}		t_cmd;

typedef struct s_local_cmd
{
  const char	*cmd;
  int		(*func)(char *);
}		t_local_cmd;

/*
** local.c
*/
int lcd_command(char *arg);
int lpwd_command(char *arg);
int lls_command(char *arg);
int lrm_command(char *arg);
int lrmdir_command(char *arg);
int lmkdir_command(char *arg);
int lhelp_command(char *arg);

/*
** login.c
*/
int	handle_login(int sock);

/*
** err.c
*/
void	err_on_socket(int socket, int eval, const char *fmt);

/*
** loop.c
*/
int	loop(int fd, int *error);

/*
**	user_input.c
*/
void	handle_user_input(t_client *client, int *err, char *buff, char *out);

/*
** cmd.c
*/
int	get_ftp_command(t_client *client, char *buffer, char *out);

/*
** recv_reply.c
*/
void	handle_recv_reply(t_client *cli, int *error, char *buffer);

/*
** data_port.c
*/
void	share_port(t_client *client);

/*
** recv_data.c
*/
void	handle_accept_data(t_client *cli,  int *error);
void	handle_recv_data(t_client *cli, int *err, char *buff);

/*
** send_data.c
*/
int	handle_send_data(t_client *client);

/*
** recv_ascii.c
*/
void	ascii_mode(char *buffer, ssize_t len, t_client *cli);

/*
** recv_bin.c
*/
void	bin_mode(char *buffer, ssize_t len, t_client *cli);

/*
** passif.c
*/
int	port_command(t_client *client, char *argument);
void	passif_mode(t_client *client);

#endif /* end of include guard: CLIENT_H_ */
