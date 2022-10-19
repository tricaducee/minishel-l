/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:25:54 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/18 17:43:02 by lgenevey         ###   ########.fr       */
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

/*
	HERMES
*/
/*
int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	t_token	*token_list;
	//char	**split;

	(void)argc;
	(void)argv;
	while (true)
	{
		init_shell(&shell, env);
		sig_handler(&shell);
		if (shell.cmdline
			&& ft_strncmp(shell.cmdline, "exit", ft_strlen(shell.cmdline) == 0))
			ft_exit(&shell);
		shell.cmdline = readline("Minishell 🍋 % ");
		if (shell.cmdline)
		{
			add_history(shell.cmdline);
			token_list = get_token(&shell);
			printf("1\n");
			print_token(token_list);
			//split = ft_split(shell.cmdline, ' ');
			free(shell.cmdline);
			free_tokens_list(token_list);
		}
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
*/


/*
	LUCIE
*/
int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	//t_token	*token_list;
	char	**split;

	(void)argc;
	(void)argv;
	while (true)
	{
		init_shell(&shell, env);
		sig_handler(&shell);
		if (shell.cmdline
			&& ft_strncmp(shell.cmdline, "exit", ft_strlen(shell.cmdline) == 0))
			ft_exit(&shell);
		shell.cmdline = readline("Minishell 🍋 % ");
		if (shell.cmdline)
		{
			add_history(shell.cmdline);
			// token_list = get_token(&shell);
			// print_token(token_list);
			split = ft_split(shell.cmdline, ' ');
			if (ft_strncmp(split[0], "env", ft_strlen(split[0])) == 0)
				ft_env(&shell);
			else if (ft_strncmp(split[0], "pwd",ft_strlen(split[0])) == 0)
				ft_pwd();
			else
			{
				is_absolute_path(split, shell.env);
				exec_cmd(split);
			}
			//free(shell.cmdline);
			//free_tokens_list(token_list);
		}
		free(shell.cmdline);
		exit(0);
	}
	return (0);
}

