/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:47 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/16 23:53:56 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
//# define PATH_MAX 2048

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
	char				**str_env;
	int					if_sig;
	int					say;
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

typedef struct S_file
{
	t_type	type;
	char	*name;
}			t_file;

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
	t_file			**file_out;
	int				and_or;
	pid_t			pid;	
	int				cmd_error;
	struct S_cmdli	*previous;
	struct S_cmdli	*next;
}					t_cmdli;

// Parsing
void		free_tab(char **ss);
t_cmdli		*cmdli_first(t_cmdli *cmds_list);
void		free_content(t_cmdli *cmdli);
void		free_cmdli(t_cmdli **cmdli);
void		free_file(t_file **files);
t_cmdli		*error_cmdli_nl(t_cmdli **cmds_list);
void		error_cmdli(t_cmdli **cmds_list, char *s);
void		error_cmdli_interpret(t_cmdli **cmds_list, char *s);
int			ft_strcmp_int(char *s1, char *s2);
int			ft_strslen(char **s);
int			files_len(t_file **files);
char		*split_cmd(char **cmdline, unsigned int *i, char c);
char		**ft_strsjoin(char *s, char **ss);
t_file		**file_join(char *file, t_file **files, t_type type);
char		*add_var(char **cmdline, char *str, unsigned int *i);
char		*add_quote(char **cmdline, char *str, unsigned int *i);
char		*add_dquote(char **cmdline, char *str, unsigned int *i);
char		*split_cmd_sp(char **cmdline, unsigned int *i);
void		print_tab(char **s);
t_cmdli		*create_cmdli(void);
void		add_pipe(t_cmdli **cmds_list, t_type *type);
void		add_andor(t_cmdli **cmds_list, t_type *type, int and_or);
void		add_arg(t_cmdli **cmds_list, char *arg, t_type *type);
void		add_cmd(t_cmdli **cmds_list, char *cmd, t_type *type);
void		file_rdi(t_cmdli **cmds_list, char *file);
void		file_rdo(t_cmdli **cmds_list, char *file, t_type type);
void		file_heredoc(t_cmdli **cmds_list, char *file);
void		add_file(t_cmdli **cmds_list, char *file, t_type *type);
void		type_and_set(char *s, t_cmdli **cmds_list,
				t_type *type, int interpret);
t_cmdli		*get_cmds(char **cmdline);
void		print_cmdli(t_cmdli *cmds_list);

// List utils
void		free_nodes(t_variable **list);
void		free_nodes_contents(t_variable **list);
void		insert_new_node(t_variable **export, t_variable *env);
t_variable	*create_node_name_value(char *name, char *value);
t_variable	*get_last_node(t_variable *list);
void		add_node_back(t_variable **list, t_variable *new);

// Init
void		init_shell(t_shell *shell, char **env);
t_shell		*ft_get_shell(t_shell *new_shell);
t_variable	*ft_get_env(void);
char		**ft_get_str_env(void);
t_variable	*ft_get_export(void);
char		*ft_get_var(char *substr);

char		*ft_prompt(void);
void		ft_print_prompt(void);
char		*get_git_path(char *cwd, char *file);
void		none_git_prompt(char *prompt, const char **prompt_elem, char *cwd);
void		git_prompt(char *prompt, const char **prompt_elem,
				char *git_path, char *cwd);
char		*get_git_branch(char *git_path);
void		prompt_cat(char *prompt, const char *element, unsigned int *i);

t_variable	*init_env(char **m_env);
char		*ft_strldup(char *s, unsigned int len);
void		split_variable(t_variable *node, char *s);
t_variable	*create_var_node(char *s);

t_variable	*init_export(void);

// Signals
void		handle_interrupt(int sig);
void		sig_handler(t_shell *shell);

void		handle_interrupt_test(int sig);
void		sig_handler_test(t_shell *shell);

// Builtins
int			ft_env(void);
int			put_node(t_variable **export, t_variable *current,
				t_variable *prev, t_variable *new);
void		ft_export(t_cmdli *cmdli);
int			ft_unset(char **args);
int			ft_pwd(void);
void		ft_exit(t_cmdli **cmdli, char *read, int mode);
int			ft_cd(t_cmdli *cmdli);
void		ft_echo(char **ss);

// ft_export_utils.c
int			export_inset(char *s);
void		free_content_node_and_print(t_cmdli *cmdli, t_variable *new, int i);

// Builtins utils
void		replace_node(t_variable **export, t_variable *new);
void		replace_node_env(t_variable *env, t_variable *new);

// Binaries
int			exec_cmd(t_cmdli *cmdli);

// Execution
int			is_builtin(t_cmdli **cmdli, char *read);
void		is_absolute_path(char **args, t_list *env);
int			ft_strchr_path(char *s, char *path, int c);
void		set_redirection(t_cmdli *cmdli);
void		set_file_out(t_cmdli *cmdli);
void		set_file_in(t_cmdli *cmdli);
char		*get_absolute_path(char *cmd, char *path);
int			close_pipe(int	*pipe);

// Readline
void		rl_replace_line(const char *text, int clear_undo);
t_token		*get_token(t_shell *shell);

// Heredoc
char		*heredoc(char *limit);

//Secure
char		**free_tab_null(char **ss);
int			return_error(char *debug);
int			exit_error(void);

//Fun
void		ft_say(char *str);
void		print_and_say(char *print, char *say);
void		print_minishell(void);

#endif
