/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 22:36:05 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	debug
*/
void	printlist(t_list *top)
{
	t_list	*elem_copy;

	elem_copy = top;
	printf("\n[printlist]\n");
	while (elem_copy)
	{
		printf("[%s]\n", ((char *)elem_copy->content));
		elem_copy = elem_copy->next;
	}
	printf("[end printlist]\n\n");
}

/*
	1er élément de la stack en haut de l'autre
	Ajouter le 1er élément de la stack x à la suite des autres de la stack y
*/
void	push(t_list *from, t_list *to)
{
	t_list	*tmp;

	if (from)
	{
		tmp = from;
		from = from->next;
		tmp->next = to;
		to = tmp;
	}
}

/*
	return the node that contains the min content
*/
t_list	*get_min_value(t_list *top)
{
	t_list	*elem_copy;
	t_list	*min;

	elem_copy = top;
	if (elem_copy == NULL)
		return (NULL);
	min = elem_copy;
	while (elem_copy)
	{
		if (ft_strcmp((char *)min->content, (char *)elem_copy->content) > 0)
		{
			// printf("min : [%s]\n", (char *)min->content);
			// printf("elem_copy : [%s]\n", ((char *)elem_copy->content));
			min = elem_copy;
		}
		elem_copy = elem_copy->next;
	}
	return (min);
}

/*
	sort by ascii table order (MAJ before min)
*/
void	sort_alphabetically(t_list *export)
{

}

void	print_export(t_list *top)
{
	t_list	*elem_copy;

	if (top == NULL)
		return ;
	elem_copy = top;
	printf("min : [%s]\n", (get_min_value(elem_copy))->content);
	while (elem_copy)
	{
		printf("declare -x %s\n", ((char *)elem_copy->content));
		elem_copy = elem_copy->next;
	}
}
