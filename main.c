/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 01:22:35 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	t_cmdli	*cmdli;
	char	*read;

	ft_get_shell(&shell);
	init_shell(&shell, env);
	(void)argc;
	(void)argv;
	while (true)
	{
		sig_handler(&shell);
		read = readline("Minishell 🍋 % ");
		if (read)
		{
			add_history(read);
			cmdli = get_cmds(&read);
			// if (!ft_strncmp(read, "exit", 4))
			// 	ft_exit(&shell, &cmdli, read);
			print_cmdli(cmdli);
			if (!is_builtin(cmdli, &shell))
				printf("c'est pas un builtin :\(\n");
			else
				printf("c'est un builtin ! :D\n");
			free_cmdli(&cmdli);
			free(read);
			free_nodes_contents(&shell.export);
			free_nodes(&shell.env);
		}
		else
		{
			free(read);
			free_nodes_contents(&shell.export);
			free_nodes(&shell.env);
			exit (0);
		}
	}
	return (0);
}
