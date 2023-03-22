
#	███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗
#	████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝
#	██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗
#	██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝
#	██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗
#	╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝

NAME = philo

CC		 = cc
CFLAGS   = -g -Wall -Werror -Wextra -pthread #-fsanitize=address #-fsanitize=thread
AR		 = ar rcs
RM		 = rm -rf
LINKFLAGS		=

SRC =		action.c		\
			checker.c		\
			init.c			\
			input.c			\
			main.c			\
			time.c			\
			utils.c			\
		

OBJS =		$(SRC:.c=.o)


$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(LINK_FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all :		$(NAME)

clean :
			$(RM) $(OBJS)

fclean :	clean
			@$(RM) $(NAME)

re :		fclean all

LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif

lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git $(REDIRECT)
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer $(REDIRECT)

.PHONY: all clean fclean re
