/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:47 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/16 15:52:15 by lgenevey         ###   ########.fr       */
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
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;


typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*redir_path;
	int				pid;
	int				stdin;
	int				stdout;
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
	t_env				*env;
	struct termios		term;
	struct sigaction	sa_interrupt;
	struct sigaction	sa_backslash;
}	t_shell;

/* Prototypes */
// Init
void	init_shell(t_shell *shell, char **env);
t_env	*init_env(char **main_envs);


// Signals
void	handle_interrupt(int sig);
void	sig_handler(t_shell *shell);

// Builtins
int		ft_env(t_shell *shell);
int		ft_pwd(void);
void	ft_exit(t_shell *shell);
void	free_envs(t_env *env);
void	exec_cmd(char **cmd);

// Execution
int		is_builtin(t_shell *shell, t_env *env);
void	is_absolute_path(char **args, t_env *env);

// Readline
void	rl_replace_line (const char *, int);
t_token	*get_token(t_shell *shell);

#endif
