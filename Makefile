# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 14:02:39 by lgenevey          #+#    #+#              #
#    Updated: 2022/10/16 18:56:58 by hrolle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c \
			srcs/binaries/build_absolute_path.c \
			srcs/binaries/execute_non_builtins.c \
			srcs/builtins/ft_env.c \
			srcs/builtins/ft_exit.c \
			srcs/builtins/ft_pwd.c \
			srcs/builtins/is_builtin.c \
			srcs/init/init_env.c \
			srcs/init/init.c \
			srcs/parsing/creates_tokens.c \
			srcs/signals/sig_handler.c

RDLINC	=	-I$(HOME)/.brew/opt/readline/include
LIBRDL =	-L$(HOME)/.brew/opt/readline/lib -lreadline

LIBFT_DIR		=	libft
LIBFT			=	libft/libft.a

OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
RM		=	rm -f

DEBUG	=	-fsanitize=address
#DEBUG	=	-g3
CFLAGS	=	-Wall -Wextra -Werror -g
INCLUDE	=	$(LIBFT_DIR) -lft

BLUE	= \033[0;34m
VIOLET	= \033[0;36m
GREEN	= \033[0;32m
RED		= \033[0;31m
YELLOW	= \033[0;33m
NONE	= \033[0m

all:	$(NAME)

$(NAME)	: $(OBJS)
	@echo "$(BLUE)Making libft and bonuses... $(NONE)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) bonus
	@$(CC) $(OBJS) $(CFLAGS) $(DEBUG) -I $(LIBFT_DIR) $(RDLINC) -L $(INCLUDE) $(LIBRDL) -o $(NAME)
	@printf "$(GREEN) $(NAME) ready.\n$(NONE)"

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(GREEN) OBJS removed.\n$(NONE)"

fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(GREEN) libft.a removed.\n$(NONE)"
	@printf "$(GREEN) $(NAME) removed.\n$(NONE)"

re: fclean all

.PHONY:	all clean fclean re
.SILENT: $(NAME) bonus clean fclean re