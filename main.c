/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/15 23:05:13 by hrolle           ###   ########.fr       */
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
		token_list = token_list->next;
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	t_token	*token_list;
	//char	**split;

	(void)argc;
	(void)argv;
	sig_handler(&shell);
	while (true)
	{
		init_shell(&shell, env);
		if (shell.cmdline
			&& ft_strncmp(shell.cmdline, "exit", ft_strlen(shell.cmdline) == 0))
			ft_exit(&shell);
		shell.cmdline = readline("Minishell 🍋 % ");
		if (shell.cmdline)
		{
			add_history(shell.cmdline);
			token_list = get_token(&shell);
			print_token(token_list);
			//split = ft_split(shell.cmdline, ' ');
			free(shell.cmdline);
			free_tokens_list(token_list);
		}
		free(shell.cmdline);
		// if (!is_builtin(&shell))
		// {
		// 	split = ft_split(&shell.cmdline);
		// 	printf("pas une builtin, faut executer avec execve\n");
		// 	build_absolute_path(split);
		// 	exec_cmd(split);
		// }
	}
	return (0);
}
