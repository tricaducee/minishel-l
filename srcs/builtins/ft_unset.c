/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:33:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/06 22:28:50 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	skip_node(t_variable *node, char *arg, int is_env)
{
	t_variable	*tmp;

	while (node->next)
	{
		if (ft_strcmp(arg, node->next->name) == 0)
		{
			tmp = node->next;
			node->next = node->next->next;
			if (!is_env)
			{
				free(tmp->name);
				free(tmp->value);
			}
			free(tmp);
			return ;
		}
		node = node->next;
	}
}

/*
	It takes one ore more arguments, UPPERCASE letters only, with OR without $
	If exists : skip next node, replace its address with next next's one
	(in both env and export lists)
*/
int	ft_unset(char **args)
{
	int			i;
	t_variable	*env;
	t_variable	*export;

	if (!args || !args[0])
		return (0);
	i = 1;
	while (args[i])
	{
		env = ft_get_env();
		export = ft_get_export();
		skip_node(env, args[i], 1);
		skip_node(export, args[i], 0);
		++i;
	}
	return (1);
}
