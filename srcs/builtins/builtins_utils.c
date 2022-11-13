/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:52:41 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/14 00:41:17 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	parcourir env, si variable deja existante alors la remplacer
	autrement ajouter le nouveau noeud a la fin
*/
void	replace_node_env(t_variable *env, t_variable *new)
{
	t_variable	*prev;

	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, new->name))
		{
			env->value = new->value;
			free(new->name);
			free(new);
			return ;
		}
		prev = env;
		env = env->next;
	}
	prev->next = malloc(sizeof(t_variable));
	if (prev->next)
	{
		prev->next->name = new->name;
		prev->next->value = new->value;
	}
}

/*
	parcourir export, si variable deja existante alors la remplacer
	autrement ajouter le nouveau noeud au bon endroit selon le tri insertion
*/
void	replace_node(t_variable **export, t_variable *new)
{
	t_variable	*prev;
	t_variable	*current;
	static int	i;

	prev = NULL;
	current = *export;
	i++;
	while (current)
	{
		if (!put_node(export, current, prev, new))
			return ;
		prev = current;
		current = current->next;
	}
	if (!current)
		prev->next = new;
}
