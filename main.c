/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 19:21:14 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/minishell.h"

#include <stdio.h>
static void	print_token(t_token *tokens)
{
	while (tokens)
	{
		printf("type = [%d] : value = [%s]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

void	free_tokens_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list;
		free(token_list->value);
		//token_list->value = NULL;
		token_list = token_list->next;
		free(tmp);
	}
}

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
		read = readline("Minishell 🍋🍑 % ");
		if (read)
		{
			add_history(read);
			cmdli = get_cmds(shell.env, read);
			print_cmdli(cmdli);
			if (!is_builtin(cmdli->cmd, &shell))
			{
				printf("c'est pas un builtin ok\n");
			}
		}
		else
		{
			free(read);
			exit (0);
		}
	}
	return (0);
}
