/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/12 19:31:02 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	t_cmdli	*cmdli;
	t_cmdli	*cmdli_i;
	char	*read;

	ft_get_shell(&shell);
	init_shell(&shell, env);
	(void)argc;
	(void)argv;
	while (true)
	{
		sig_handler(&shell);
		read = readline(ft_prompt());
		if (read)
		{
			if (*read)
				add_history(read);
			cmdli = get_cmds(&read);
			if (cmdli)
			{
				cmdli_i = cmdli;
				while (cmdli_i)
				{
					if (!is_builtin(&cmdli_i, read))
						exec_cmd(cmdli_i);
					cmdli_i = cmdli_i->next;
				}
				while (wait(NULL) != -1)
					;
				free_cmdli(&cmdli);
			}
			free(read);
		}
		else
			ft_exit(&cmdli, read, 0);
	}
	free_nodes_contents(&shell.export);
	free_nodes(&shell.env);
	return (0);
}
