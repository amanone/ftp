/*
** builtin_cd.c for builtin_cd in /home/coudra_t/42/builtins
**
** Made by thomas coudray
** Login <coudra_t@epitech.net>
**
** Started on Mon Apr 18 17:08:12 2011 thomas coudray
** Last update Sun May 22 22:54:05 2011 thomas coudray
*/

#ifndef SERVER_H_

# define SERVER_H_

# include <netdb.h>
# include <sys/queue.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>

#define	FILE_CONFIG		("serveur.conf")

# define IS_ACTIVE(x)		(x != -1 ? 1 : 0)
# define MAX(x, y)		(x > y ? x : y)
# define MIN(x, y)		(x < y ? x : y)

# define OFF			(0)
# define ON			(1)

# define BUFFER_SIZE		(1024)
# define BUFFER_OUT		(2048)

# define DEFAULT_PORT		(4242)

# define ASCII_MODE		(0xCAFED00D)
# define BIN_MODE		(0xCAFEBABE)

# define UC(x)  ((int)		(((int) x) & 0xff))

# define DEFAULT_USER		("anonymous")

# define CONNECTING		"220 amanone-ftpd 0.01\r\n"
# define NOT_AUTH		"530 Please login with USER and PASS.\r\n"
# define LOGIN_FAIL		"530 Login incorrect.\r\n"
# define USER_BEFORE_LOGIN	"530 USER BEFORE PASS.\r\n"
# define BAD_CMD		"500	Bad command.\r\n"

# define CODE_PWD_OK		"257 "
# define CODE_PWD_FAIL		"550 Requested action not taken.\r\n"

# define CODE_CD_FAIL_HOME	"550 Failled to change directory to home.\r\n"
# define CODE_CD_OK_HOME	"250 Directory success' changed to home.\r\n"
# define CODE_CD_FAIL		"550 Failed to change directory.\r\n"
# define CODE_CD_OK		"250 Directory successfully changed.\r\n"

# define CODE_LS_FAIL		"550 Requested action cannot allocate mem.\r\n"

# define CODE_PORT_NO_ARG	"550 Bad format : PORT h1,h2,h3,h4,p1,p2.\r\n"
# define CODE_PORT_BAD_ARG	"550 Bad format : Missing separator.\r\n"

# define PORT_OK		"200 PORT Ok. Consider using PASV.\r\n"
# define PORT_FAIL		"425 Cannot open DATA connection.\r\n"

# define LIST_BEGIN		"150 Here comes the directory listing.\r\n"
# define LIST_ERROR		"550 Requested action not taken.\r\n"
# define LIST_ERROR_M		"550 Requested action fail. Not enough mem\r\n"
# define END_DATA_LS		"226 Directory send OK.\r\n"
# define CLOSE_DATA		"552 Requested action failed, Close Data.\r\n"

# define NEED_PASS		"331 Please specify the password.\r\n"
# define LOGIN_SUCCESS		"230 Login successful.\r\n"
# define LOGIN_FAIL		"530 Login incorrect.\r\n"

# define USAGE_GET		"530 get [file].\r\n"
# define ERROR_RETR_OPEN	"550 Failed to open file.\r\n"
# define RETR_BEGIN_A		"150 Opening ASCII mode DATA connection.\r\n"
# define RETR_BEGIN_B		"150 Opening BINARY mode DATA connection.\r\n"
# define END_DATA_RETR		"226 File send OK.\r\n"

# define USAGE_PUT		"530 put [file].\r\n"
# define ERROR_STOR_OPEN	"550 Failed to create file.\r\n"
# define STOR_BEGIN_A		"150 Opening ASCII mode DATA connection.\r\n"
# define STOR_BEGIN_B		"150 Opening BINARY mode DATA connection.\r\n"
# define END_DATA_STOR		"226  File recive OK.\r\n"

# define CODE_ASC_MODE		"200 Switching to ASCII mode.\r\n"
# define CODE_BIN_MODE		"200 Switching to Binary mode.\r\n"

# define DEFAULT_MODE		"200 Switching to default mode : ASCII.\r\n"

# define BAD_PARAM_TYPE		"500 TYPE Has no parameter.\r\n"

# define BAD_ARG_DELE		"500 DELE [remote-filename].\r\n"
# define BAD_ARG_RMD		"500 DELE [remote-directory].\r\n"
# define FAIL_DEL		"500 Failed to delete file.\r\n"
# define SUCCESS_DEL		"210 Success delete file.\r\n"

# define BAD_ARG_MKD		"500 MKDE [remote-filename].\r\n"
# define FAIL_MKD		"500 Failed to mkdir.\r\n"
# define SUCCESS_MKD		"210 Success to mkdir.\r\n"

# define BAD_ARG_NLST		"500 NLST [remote-dir].\r\n"
# define FAIL_NLST		"500 Failed to nlst.\r\n"
# define SUCCESS_NLST		"210 Success to nlst.\r\n"

# define BAD_ARG_RN		"500 RNFR [remote-file].\r\n"
# define FAIL_RN		"500 Failed to rename file.\r\n"
# define SUCCESS_RENAME		"210 Success to rename file.\r\n"

# define SUCCESS_CHMOD		"210 Success to change file permissions.\r\n"
# define FAIL_CHMOD		"500 Failed to change file permissions.\r\n"

# define SYS_INFO		"215 UNIX Type: L8\r\n"

# define CRYPT_FAIL		"500 Failed to crypt mdp\r\n"

# define COMMAND(NAME)		{#NAME, NAME ## _command}

typedef struct		s_opt
{
  char			*file;
  int			flags;
}			t_opt;

enum	  		 e_opt
{
  opt_daemonize   = 1 << 0,
  opt_config_file = 1 << 1,
  opt_ipv6	  = 1 << 2,
  opt_secure	  = 1 << 3,
  opt_verbose     = 1 << 4
};

t_opt			g_opt;

typedef struct		t_user
{
  char			*user;
  char			*pass;
  char			*root;
  SLIST_ENTRY(t_user)	next;
}			t_user;

typedef SLIST_HEAD(listhead, t_user)	t_listhead;

typedef struct		s_client
{
  char			*arg;
  char			*cmd;
  char			mode_trans;
  char			*home;
  char			*login;
  char			*long_arg;
  char			*masterdir;
  char			*tmpfile;
  char			*to_free;
  char	  		*curdir;
  int			auth;
  int			bell_end;
  int			data_connected;
  int			flags_rename;
  int			has_login;
  int			opt;
  int			run;
  int			sock;
  pid_t			mpid;
  pid_t			pidmaster;
  size_t		mode;
  t_listhead		list;
}			t_client;

typedef struct		s_cmd
{
  const char		*cmd_in;
  int			(*func)(t_client *);
}			t_cmd;

/*
 ** config.c
 */
t_listhead	handle_config(void);

/*
 ** err.c
 */
void		err_on_socket(int socket, int eval, const char *fmt);

/*
 ** cmd.c
 */
int		handle_cmd(t_client *);

/*
 ** cmd_pwd.c
 */
void		get_rootdir(char *, t_client *);
int		pwd_command(t_client *);

/*
 ** cmd_cd.c
 */
int		cwd_command(t_client *);

/*
 ** cmd_ls.c
 */
int		loop_list(int , struct dirent **, char *, t_client *);
int		list_command(t_client *);

/*
 ** cmd_ls_utilities.c
 */
int		stat_file(char *, char *, char *, t_client*);
void		fill_buff(struct stat, char *, size_t, char*);

/*
 ** auth.c
 */
int		authenticator(t_client *);

/*
 ** connect_server.c
 */
int		connect_server(t_listhead, int);

/*
 ** parse.c
 */
int		format_input(char *, ssize_t, t_client *);

/*
 ** run_life.c
 */
int		run_life_son(int, pid_t, struct sockaddr_in *, t_listhead);

/*
 ** cmd_*.c
 */
int		asc_command(t_client *client);
int		bin_command(t_client *client);
int		list_command(t_client *client);
int		pass_command(t_client *client);
int		port_command(t_client *client);
int		quit_command(t_client *client);
int		retr_command(t_client *client);
int		stor_command(t_client *client);
int		type_command(t_client *client);
int		user_command(t_client *client);
int		cdup_command(t_client *client);
int		dele_command(t_client *client);
int		rmd_command(t_client *client);
int		mkd_command(t_client *client);
int		syst_command(t_client *client);
int		rnfr_command(t_client *client);
int		rnto_command(t_client *client);
int		mget_command(t_client *client);
int		pasv_command(t_client *client);
int		site_command(t_client *client);
int		chmod_command(t_client *client);
int		bell_command(t_client *client);

#endif /* end of include guard: SERVER_H_ */
