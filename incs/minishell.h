/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:47 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/31 19:12:18 by lgenevey         ###   ########.fr       */
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

// Readline
# include <readline/readline.h>
# include <readline/history.h>

//globale pour recuperer la valeur du statut de exit
int	g_errno;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;

typedef struct s_shell
{
	t_variable			*env;
	t_variable			*export;
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

typedef struct S_cmdli
{
	char			*cmd;
	char			**cmd_args;
	int				*pipe_in;
	int				*pipe_out;
	char			*here_doc;
	int				fd_in;
	int				fd_out;
	char			**file_in;
	char			**file_out;
	t_type			file_type;
	int				and_or;
	struct S_cmdli	*previous;
	struct S_cmdli	*next;
}					t_cmdli;

// Parsing
t_cmdli		*get_cmds(t_variable *env, char *cmdline);
void		print_cmdli(t_cmdli *cmds_list);
char		*heredoc(char *limit);
void		free_cmdli(t_cmdli **cmdli);

// List utils
void		printlist(t_variable *top);
void		sort_insertion(t_variable *export);
char		*ft_get_env(t_variable *env, char *substr);
t_variable	*create_t_variable_node(char *s);
void		free_nodes_contents(t_variable **list);
void		free_nodes(t_variable **list);

// Init
void		init_shell(t_shell *shell, char **env);
t_variable	*init_env(char **m_env);
t_variable	*init_export(t_variable *env);

// Signals
void		handle_interrupt(int sig);
void		sig_handler(t_shell *shell);

// Builtins
int			ft_env(t_shell *shell);
int			ft_export(t_shell *shell, t_cmdli *cmdli);
int			ft_pwd(void);
void		ft_exit(t_shell *shell);
void		ft_echo(char **ss);

// Binaries
void		exec_cmd(char **cmd);

// Execution
int			run_builtin(const char *str, t_cmdli *cmd, t_shell *shell, int len);
int			is_builtin(t_cmdli *cmd, t_shell *shell);
void		is_absolute_path(char **args, t_list *env);

// Readline
void		rl_replace_line(const char *text, int clear_undo);
t_token		*get_token(t_shell *shell);

// Heredoc
char		*heredoc(char *limit);

#endif
