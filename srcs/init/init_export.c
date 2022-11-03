/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 02:41:26 by hrolle           ###   ########.fr       */
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
	t_variable *node;

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
		sort_alpha(&export, create_node_name_value(env->name, env->value));
		env = env->next;
	}
	sort_alpha(&export, create_node_name_value(ft_strdup("OLDPWD"), NULL));
	return (export);
}

/*
	creer le premier noeud export
	initialiser son contenu avec le contenu du premier noeud de env
	garder en memoire ce pointeur sur le premier noeud de export
	parcourir env
		parcourir export et comparer chaque noeud avec env
		si plus grand, ajouter a export.next
		si plus petit ajouter a export.prev

*/

// t_variable	*insertion_sort(t_variable *sorted_head, t_variable *current)
// {
// 	t_variable	*tmp;

// 	tmp = NULL;
// 	if (sorted_head == NULL || ft_strcmp(sorted_head->name, current->name) > 0)
// 	{
// 		current->next = sorted_head;
// 		return (current);
// 	}
// 	else
// 	{
// 		tmp = sorted_head;
// 		while (tmp->next != NULL && ft_strcmp(tmp->next->name, current->name) < 0)
// 			tmp = tmp->next;
// 		current->next = tmp->next;
// 		tmp->next = current;
// 	}
// 	return (sorted_head);
// }

// t_variable	*init_export(t_variable *head)
// {
// 	t_variable	*current;
// 	t_variable	*sorted_head;
// 	t_variable	*current_next;

// 	current = head;
// 	sorted_head = NULL;
// 	while (current)
// 	{
// 		current_next = current->next;
// 		sorted_head = insertion_sort(sorted_head, current);
// 		current = current->next;
// 	}
// 	return (sorted_head);
// }
