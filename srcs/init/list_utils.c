/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/02 18:17:38 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	free node address (used for env linked list)
*/
void	free_nodes(t_variable **list)
{
	t_variable	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

/*
	free node address and node content (name and value)
	(used for export linked list)
*/
void	free_nodes_contents(t_variable **list)
{
	t_variable	*tmp;

	while (*list)
	{
		if ((*list)->name)
			free((*list)->name);
		if ((*list)->value)
			free((*list)->value);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

/*
	faire un tri par insertion a l'occasion
*/
static void ft_swap(t_variable *a, t_variable *b)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = a->name;
	tmp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = tmp_name;
	b->value = tmp_value;
}

/*
	Bubble sort : sort export linked list for initialization.
*/
void	sort_alpha(t_variable *export)
{
	int swapped;
	t_variable *compared;
	t_variable *tmp;

	if (export == NULL)
		return ;
	swapped = 1;
	tmp = NULL;
	while (swapped)
	{
		swapped = 0;
		compared = export;

		while (compared->next != tmp)
		{
			if (ft_strcmp(compared->name, compared->next->name) > 0)
			{
				ft_swap(compared, compared->next);
				swapped = 1;
			}
			compared = compared->next;
		}
		tmp = compared;
	}
}
