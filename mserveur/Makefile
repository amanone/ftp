##
## Makefile for 42sh in /home/coudra_t/Workspace/42sh
##
## Made by thomas coudray
## Login <coudra_t@epitech.net>
##
## Started on Thu May 5 17:52:24 2011 thomas coudray
## Last update Sun Jun 12 19:08:06 2011 thomas coudray
##

NAME	=	../serveur

DEBUG	=	no

SRC	=	main.c			\
		auth.c			\
		cmd.c			\
		cmd_dele.c		\
		cmd_ls.c		\
		cmd_ls_utilities.c	\
		cmd_mget.c		\
		cmd_mkd.c		\
		cmd_pass.c		\
		cmd_pasv.c		\
		cmd_port.c		\
		cmd_quit.c		\
		cmd_retr.c		\
		cmd_rmd.c		\
		cmd_rnfr.c		\
		cmd_site.c		\
		cmd_stor.c		\
		cmd_type.c		\
		cmd_user.c		\
		config.c		\
		connect_server.c	\
		err.c			\
		parse.c			\
		run_life.c		\
                cmd_cd.c		\
                cmd_pwd.c		\

OBJ	=	$(SRC:.c=.o)
DEPS	=	$(SRC:.c=.d)

RM	=	rm -rf
CC	=	gcc
FIND	=	find

ifeq ($(DEBUG),yes)
	WFLAGS	=  -g3 -ggdb
	CC = clang
else
  WFLAGS	= -W -Wall -Wextra
	CC = gcc
endif

CFLAGS	+=	$(WFLAGS) -D_GNU_SOURCE -lcrypt

MAKE   	= 	@make --no-print-directory
PRINTF	=	/usr/bin/printf

all:
		$(MAKE) $(NAME)

$(NAME): 	$(OBJ)
		$(CC) $^ -o $(NAME) $(LDFLAGS) $(CFLAGS)

%.o:		 %.c
	         $(CC) -c $< -o $@ $(CFLAGS)

%.d:	 	%.c
		 $(CC) -MM -MT $(<:.c=.o) -o $@ $< $(CFLAGS)

clean:
		@$(RM) $(OBJ)
		@$(FIND) . -name "*#*#" -exec $(RM) {} \;
		@$(FIND) . -name "*~"   -exec $(RM) {} \;

fclean:
		$(MAKE) clean
		$(MAKE) clean-depend
		@$(RM) $(NAME)

mrpropre:
		$(MAKE) all
		$(MAKE) clean

re:
		$(MAKE) fclean
		$(MAKE) all

depend:
		$(MAKE) $(DEPS)

clean-depend:
		$(RM) $(DEPS)

coffee	:
			@echo  "       A"
			@echo  "      AM"
			@echo  "     AMA"
			@echo  "    AMANO"
			@echo  "     AMANON"
			@echo  "      AMANONE"
			@echo  "    AMANONEAMA"
			@echo  " _______________"
			@echo  "|               |___"
			@echo  "|               |   \ "
			@echo  "|               |   |"
			@echo  "|               |___|"
			@echo  "|               |"
			@echo  " \_____________/"
			@echo	""

.PHONY : all clean depend clean-depend fclean coffee

-include $(DEPS)
