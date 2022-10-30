/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/30 16:27:43 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	t_cmdli	*cmdli;
	char	*read;

	(void)argc;
	(void)argv;
	while (true)
	{
		init_shell(&shell, env);
		sig_handler(&shell);
		read = readline("Minishell 🍋 % ");
		if (read)
		{
			add_history(read);
			cmdli = get_cmds(shell.env, read);
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
		//ft_lstclear(&shell.export, free);
	}
	return (0);
}
