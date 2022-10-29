/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/28 09:02:09 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

#include <stdio.h>

// void	free_tokens_list(t_token *token_list)
// {
// 	t_token	*tmp;

// 	while (token_list)
// 	{
// 		tmp = token_list;
// 		free(token_list->value);
// 		token_list = token_list->next;
// 		free(tmp);
// 	}
// }

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
			//ft_get_env(shell.env, "PATH");
			if (!is_builtin(cmdli, &shell))
				printf("c'est pas un builtin :\(\n");
			else
				printf("c'est un builtin ! :D\n");
			free_cmdli(&cmdli);
			free(read);
		}
		else
		{
			free(read);
			exit (0);
		}
		//ft_lstclear(&shell.env, free);
	}
	return (0);
}

//fonction free noeud de liste
// fonction free strings de chaque noeud