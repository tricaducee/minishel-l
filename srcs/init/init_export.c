/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/31 20:09:47 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	creates new node for t_variable linked list
*/
static t_variable	*create_node(t_variable *env)
{
	t_variable *node;

	node = (t_variable *)malloc(sizeof(t_variable));
	if (!node)
		return (NULL);
	node->name = env->name;
	node->value = env->value;
	node->next = NULL;
	return (node);
}

/*
	Creates a copy of env linked list in an other linked list
	Add OLDPWD alone as the real bash export does
	Returns a t_variable export sorted
*/
t_variable	*init_export(t_variable *env)
{
	t_variable	*ret;
	t_variable	*export;

	if (!env)
		return (NULL);
	export = create_node(env);
	ret = export;
	env = env->next;
	while (env)
	{
		export->next = create_node(env);
		export = export->next;
		env = env->next;
	}
	export->next = NULL;
	sort_alpha(ret);
	return (ret);
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
