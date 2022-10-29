/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/29 16:42:02 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print la liste chainee stockee dans la struc shell.export
*/
static void	print_export(t_list *top)
{
	t_list	*top_copy;

	if (top == NULL)
		return ;
	top_copy = top;
	while (top_copy)
	{
		printf("declare -x %s\n", (top_copy->content));
		top_copy = top_copy->next;
	}
}

int	ft_export(t_shell *shell, t_cmdli *cmdli)
{
	if (!cmdli->cmd_args)
	{
		print_export(shell->export);
		return (1);
	}
	while (*cmdli->cmd_args)
	{
		printf("ft_export string : [%s]\n", *cmdli->cmd_args);
		while (!ft_is_uppercase(*cmdli->cmd_args) && *cmdli->cmd_args)
		{
			printf("ft_export not upper : [%s]\n", *cmdli->cmd_args);
			++cmdli->cmd_args;
		}
		printf("ft_export is upper : [%s]\n", *cmdli->cmd_args);
		++cmdli->cmd_args;
	}
	return (1);
}
