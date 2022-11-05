/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:33:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/04 18:51:41 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void	skip_node(t_variable *node, char *arg)
{
	while (node->next)
	{
		if (ft_strcmp(arg, node->next->name) == 0)
		{
			node->next = node->next->next;
			break ;
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
		skip_node(export, args[i]);
		skip_node(env, args[i]);
		++i;
	}
	return (1);
}

/*
	Parcourir le char **
	Si nom strictement identique a une variable alors le skip
	faire une fonction qui skip un noeud, prend en entree un t_variable *node

*/