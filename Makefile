##
## Makefile for wolf in /home/coudra_t/projet/r/lol
## 
## Made by thomas coudray
## Login   <coudra_t@epitech.net>
## 
## Started on  Fri Mar 11 18:04:13 2011 thomas coudray
## Last update Sun Mar 13 22:58:37 2011 thomas coudray
##

all:
	make -C ./mclient
	make -C ./mserveur

clean:
	make clean -C ./mclient
	make clean -C ./mserveur

fclean:
	make fclean -C ./mclient
	make fclean -C ./mserveur

re:	fclean all

client:
	make -C ./mclient

serveur:
	make -C ./mserveur

coffee:
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
	@echo	"kkk"

.PHONY:	all clean fclean re coffee serveur client
