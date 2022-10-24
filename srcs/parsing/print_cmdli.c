#include "get_cmds.h"

static void	print_tab(char **ss)
{
	if (!ss || !*ss)
		printf("cmd_args = (null)\n");
	else
	{
		printf("cmd_args = %s\n", *(ss++));
		while (*ss)
			printf("           %s\n", *(ss++));
	}
}

void	print_cmdli(t_cmdli *cmds_list)
{
	unsigned int	i = 0;

	printf("\nCMDLI :\n");
	if (!cmds_list)
	{
		printf("cmds_list = NULL\n");
		return ;
	}
	while (cmds_list)
	{
		printf("\nnode %u :\n\n", ++i);
		printf("cmd_path = %s\n", cmds_list->cmd_path);
		print_tab(cmds_list->cmd_args);
		if (cmds_list->pipe_in)
			printf("pipe_in = yes\n");
		else
			printf("pipe_in = no\n");
		if (cmds_list->pipe_out)
			printf("pipe_out = yes\n");
		else
			printf("pipe_out = no\n");
		printf("fd_in = %d\n", cmds_list->fd_in);
		printf("fd_out = %d\n", cmds_list->fd_out);
		printf("here_doc = %s\n", cmds_list->here_doc);
		printf("and_or = %d\n", cmds_list->and_or);
		printf("next = %p\n", cmds_list->next);
		printf("previous = %p\n", cmds_list->previous);
		cmds_list = cmds_list->next;
	}
}