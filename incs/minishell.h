/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:47 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/22 23:08:22 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/termios.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Parsing hrolle
#include "../srcs/parsing/get_cmds.h"

//globale pour recuperer la valeur du statut de exit

//token list
enum e_tokens
{
	UNKNOWN_TOKEN = 0,
	COMMAND,
	OPTION,
	PIPE,
	ENV_VARIABLE,
	REDIRECTION
};

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

// contains a copy of env variables
// typedef struct s_env
// {
// 	char			*name;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*redir_path;
	int				pid;
	int				std_in;
	int				std_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char				*cmdline;
	char				*prompt;
	char				**tokens;
	int 				std_in;
	int					std_out;
	t_cmd				*cmd;
	t_list				*env;
	t_list				*export;
	struct termios		term;
	struct sigaction	sa_interrupt;
	struct sigaction	sa_backslash;
}	t_shell;

// List utils
t_list	*get_last_env(t_list *node);
t_list	*new_env_node(char	*name, char *value);
void	env_add_back(t_list **lst, t_list *new);
void	printlist(t_list *list);
void	print_export(t_list *elem);

// Init
void	init_shell(t_shell *shell, char **env);
t_list	*fill_env(char **m_env);
t_list	*fill_export(t_list *env);

// Signals
void	handle_interrupt(int sig);
void	sig_handler(t_shell *shell);

// Builtins
int		ft_env(t_shell *shell);
int		ft_export(t_shell *shell);
int		ft_pwd(void);
void	ft_exit(t_shell *shell);

// Binaries
void	exec_cmd(char **cmd);

// Execution
int		is_builtin(t_shell *shell, t_list *env);
void	is_absolute_path(char **args, t_list *env);

// Readline
void	rl_replace_line (const char *, int);
t_token	*get_token(t_shell *shell);

#endif
