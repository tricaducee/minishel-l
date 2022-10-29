/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmdli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 06:53:43 by hrolle            #+#    #+#             */
/*   Updated: 2022/10/28 02:00:32 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	print_tab(char **ss, char *s)
{
	if (!ss || !*ss)
		printf("%s = (null)\n", s);
	else
	{
		printf("%s = %s\n", s, *(ss++));
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
		printf("cmd = %s\n", cmds_list->cmd);
		print_tab(cmds_list->cmd_args, "cmd_args");
		if (cmds_list->pipe_in)
			printf("pipe_in = yes\n");
		else
			printf("pipe_in = no\n");
		if (cmds_list->pipe_out)
			printf("pipe_out = yes\n");
		else
			printf("pipe_out = no\n");
		print_tab(cmds_list->file_in, "file_in");
		print_tab(cmds_list->file_out, "file_out");
		printf("file_type = %d\n", cmds_list->file_type);
		printf("here_doc = %s\n", cmds_list->here_doc);
		printf("and_or = %d\n", cmds_list->and_or);
		printf("next = %p\n", cmds_list->next);
		printf("previous = %p\n", cmds_list->previous);
		cmds_list = cmds_list->next;
	}
}