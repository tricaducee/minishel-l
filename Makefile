# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 14:02:39 by lgenevey          #+#    #+#              #
#    Updated: 2022/10/19 14:31:30 by lgenevey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c \
			srcs/binaries/build_absolute_path.c \
			srcs/binaries/execute_non_builtins.c \
			srcs/builtins/ft_env.c \
			srcs/builtins/ft_exit.c \
			srcs/builtins/ft_pwd.c \
			srcs/execution/is_builtin.c \
			srcs/init/init_env.c \
			srcs/init/init_env_export.c \
			srcs/init/init.c \
			srcs/parsing/creates_tokens.c \
			srcs/signals/sig_handler.c

#RDLINC	=	-I/Users/hrolle/.brew/opt/readline/include
#LIBRDL =	-L/Users/hrolle/.brew/opt/readline/lib -lreadline

INC_FLAGS := -Ilibs/libft/incs -Iincs
LIBS := -Llibft -lft -lreadline

INC_FLAGS += -I$(HOME)/.brew/opt/readline/include
LIBS += -L$(HOME)/.brew/opt/readline/lib

OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
RM		=	rm -f

DEBUG	=	-fsanitize=address
#DEBUG	=	-g3
#CFLAGS	=	-Wall -Wextra -Werror -g

BLUE	= \033[0;34m
VIOLET	= \033[0;36m
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
NONE	= \033[0m

all:	$(NAME)

$(NAME)	: $(OBJS)
	@echo "$(BLUE)Making libft and bonuses... $(NONE)"
	@$(MAKE) -C libft
	@$(MAKE) -C libft bonus
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(LIBS) $(DEBUG) -o $(NAME)
	@printf "$(GREEN) $(NAME) ready.\n$(NONE)"

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C libft clean
	@printf "$(GREEN) OBJS removed.\n$(NONE)"

fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@printf "$(GREEN) libft.a removed.\n$(NONE)"
	@printf "$(GREEN) $(NAME) removed.\n$(NONE)"

re: fclean all

.PHONY:	all clean fclean re
.SILENT: $(NAME) bonus clean fclean re