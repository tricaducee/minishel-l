/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/05 06:47:57 by lgenevey         ###   ########.fr       */
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
			add_history(read);
			cmdli = get_cmds(&read);
			// if (!ft_strncmp(read, "exit", 4))
			// 	ft_exit(&shell, &cmdli, read);
			if (cmdli)
			{
				//print_cmdli(cmdli);
				cmdli_i = cmdli;
				while (cmdli_i)
				{
					if (!is_builtin(cmdli_i))
					{
						printf("c'est pas un builtin :\(\n");
						exec_cmd(cmdli_i);
					}
					else
					{
						printf("c'est un builtin ! :D\n");
					}
					cmdli_i = cmdli_i->next;
				}
				while (wait(NULL) != -1)
					;
				free_cmdli(&cmdli);
			}
			free(read);
		}
		else
		{
			free(read);
			read = ft_prompt();
			if (read)
				free(read);
			free_nodes_contents(&shell.export);
			free_nodes(&shell.env);
			exit (0);
		}
	}
	free_nodes_contents(&shell.export);
	free_nodes(&shell.env);
	return (0);
}
