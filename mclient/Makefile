##
## Makefile for 42sh in /home/coudra_t/Workspace/42sh
##
## Made by thomas coudray
## Login <coudra_t@epitech.net>
##
## Started on Thu May 5 17:52:24 2011 thomas coudray
## Last update Sun Jun 12 19:08:06 2011 thomas coudray
##

# libreadline5-dev

NAME	=	../client

DEBUG	=	no

SRC	=	main.c		\
		cmd.c		\
		data_port.c	\
		err.c		\
		get_cmd.c	\
		local.c		\
		local_ls.c	\
		login.c		\
		loop.c		\
		passif.c	\
		recv_ascii.c	\
		recv_bin.c	\
		recv_data.c	\
		recv_reply.c	\
		send_data.c	\
		user_input.c	\

OBJ	=	$(SRC:.c=.o)
DEPS	=	$(SRC:.c=.d)

RM	=	rm -rf
CC	=	gcc
FIND	=	find

ifeq ($(DEBUG),yes)
	WFLAGS	= -W -g3
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
