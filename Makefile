
#	███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗
#	████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝
#	██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗
#	██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝
#	██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗
#	╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝

NAME = philo

CC		 = cc
CFLAGS   = -g -Wall -Werror -Wextra -pthread
AR		 = ar rcs
RM		 = rm -rf

#.SILENT:
#			printf
#			clean
#			all
#			$(NAME)

SRC =		action.c		\
			checker.c		\
			init.c			\
			input.c			\
			main.c			\
			time.c			\
			utils.c			\
		

OBJS =		$(SRC:.c=.o)


$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all :		$(NAME)

clean :
			$(RM) $(OBJS)

fclean :	clean
			@$(RM) $(NAME)

re :		fclean all

.PHONY: all clean fclean re
