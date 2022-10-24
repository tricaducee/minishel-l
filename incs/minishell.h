/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:47 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 17:36:57 by lgenevey         ###   ########.fr       */
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
# include <limits.h>
# include "../libft/libft.h"

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Parsing hrolle
# include "../srcs/parsing/get_cmds.h"

//globale pour recuperer la valeur du statut de exit

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

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
	t_cmdli				*cmdline;
	t_list				*env;
	t_list				*export;
	struct termios		term;
	struct sigaction	sa_interrupt;
	struct sigaction	sa_backslash;
}	t_shell;

// List utils
void	printlist(t_list *top);
void	push(t_list *from, t_list *to);
void	sort_alphabetically(t_list *export);

// Init
void	init_shell(t_shell *shell, char **env);
t_list	*fill_env(char **m_env);
t_list	*init_export(t_list *env);

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
int		run_builtin(const char *str, int len, t_cmdli *cmdli, t_shell *shell);
int		is_builtin(t_cmdli *cmdli, t_shell *shell);
void	is_absolute_path(char **args, t_list *env);

// Readline
void	rl_replace_line (const char *, int);
t_token	*get_token(t_shell *shell);

#endif
