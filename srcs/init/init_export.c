/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/31 19:07:02 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Creates a copy of env linked list in an other linked list
	Add OLDPWD alone as the real bash export does
	Returns a t_variable export sorted
*/
// t_variable	*init_export(t_variable *env)
// {
// 	t_variable	*export;
// 	t_variable	*ret;
// 	t_variable	*env_cpy;

// 	if (!env)
// 		return (NULL);
// 	export = (t_variable *)malloc(sizeof(t_variable));
// 	if (!export)
// 		return (NULL);
// 	ret = export;
// 	env_cpy = env;
// 	while (env_cpy)
// 	{
// 		export->name = env_cpy->name;
// 		export->value = env_cpy->value;
// 		export->next = 	(t_variable *)malloc(sizeof(t_variable));
// 		if (!export->next)
// 			return (NULL);
// 		export = export->next;
// 	}
// 	export->name = ft_strdup("OLDPWD");
// 	export->value = ft_strdup("");
// 	export->next = NULL;
// 	sort_insertion(export);
// 	return (ret);
// }

/*
	creer le premier noeud export
	initialiser son contenu avec le contenu du premier noeud de env
	garder en memoire ce pointeur sur le premier noeud de export
	parcourir env
		parcourir export et comparer chaque noeud avec env
		si plus grand, ajouter a export.next
		si plus petit ajouter a export.prev

*/

t_variable	*insertion_sort(t_variable *sorted_head, t_variable *current)
{
	t_variable	*tmp;

	tmp = NULL;
	if (sorted_head == NULL || ft_strcmp(sorted_head->name, current->name) > 0)
	{
		current->next = sorted_head;
		return (current);
	}
	else
	{
		tmp = sorted_head;
		while (tmp->next != NULL && ft_strcmp(tmp->next->name, current->name) < 0)
			tmp = tmp->next;
		current->next = tmp->next;
		tmp->next = current;
	}
	return (sorted_head);
}

t_variable	*init_export(t_variable *head)
{
	t_variable	*current;
	t_variable	*sorted_head;
	t_variable	*current_next;

	current = head;
	sorted_head = NULL;
	while (current)
	{
		current_next = current->next;
		sorted_head = insertion_sort(sorted_head, current);
		current = current->next;
	}
	return (sorted_head);
}
