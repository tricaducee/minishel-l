/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/12 19:30:48 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	creates new node for t_variable linked list
	t_variable *env : source data
	returns new node with datas
*/
t_variable	*create_node_name_value(char *name, char *value)
{
	t_variable	*node;

	node = malloc(sizeof(t_variable));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

/*
	Creates a copy of env linked list in an other linked list
	Add OLDPWD alone as the real bash export does
	Returns a t_variable export sorted
*/
t_variable	*init_export(void)
{
	t_variable	*export;
	t_variable	*env;

	env = ft_get_env();
	if (!env)
		return (NULL);
	export = create_node_name_value(env->name, env->value);
	env = env->next;
	while (env)
	{
		insert_new_node(&export, create_node_name_value(env->name, env->value));
		env = env->next;
	}
	insert_new_node(&export, create_node_name_value(ft_strdup("OLDPWD"), NULL));
	return (export);
}
