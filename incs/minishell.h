/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:47 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 18:22:45 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/termios.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../srcs/parsing/get_cmds.h"

// Readline
# include <readline/readline.h>
# include <readline/history.h>

//globale pour recuperer la valeur du statut de exit

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	t_list				*env;
	t_list				*export;
	struct termios		term;
	struct sigaction	sa_interrupt;
	struct sigaction	sa_backslash;
}	t_shell;

typedef enum e_type
{
	EMPTY,
	CMD,
	ARG,
	PIPE,
	RFILE,
	RDI,
	RDO,
	RDIH,
	RDOA,
	ANDOR
}			t_type;

typedef struct	S_cmdli
{
	char			*cmd;
	char			**cmd_args;
	int				*pipe_in;
	int				*pipe_out;
	char			*here_doc;
	int				fd_in;
	int				fd_out;
	int				and_or;
	struct S_cmdli	*previous;
	struct S_cmdli	*next;
}					t_cmdli;

// Parsing

t_cmdli	*get_cmds(t_list *env, char *cmdline);
void	print_cmdli(t_cmdli *cmds_list);

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
