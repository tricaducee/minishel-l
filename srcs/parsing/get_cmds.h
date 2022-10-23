#ifndef GET_CMDS_H
# define GET_CMDS_H
# include <stdlib.h>

typedef enum e_type
{
	EMPTY,
	CMD,
	ARG,
	PIPE,
	FILE,
	RED,
	ANDOR
}			t_type;

typedef struct	S_cmdli
{
	char			*cmd_path;
	char			**cmd_args;
	int				**pipe_in;
	int				**pipe_out;
	char			*here_doc;
	int				fd_in;
	int				fd_out;
	int				and_or;
	struct S_cmdli	*previous;
	struct S_cmdli	*next;
}					t_cmdli;

t_cmdli	*get_cmds(char *cmdline);

#endif
