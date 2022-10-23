/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/23 16:12:07 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print a list from a copy pointer
*/
void	printlist(t_list *top)
{
	t_list	*elem_copy;

	elem_copy = top;
	while (elem_copy)
	{
		printf("%s\n", ((char *)elem_copy->content));
		elem_copy = elem_copy->next;
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
			min = elem_copy;
		elem_copy = elem_copy->next;
	}
	return (min);
}

void ft_swap(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

/*
	prend export en argument (liste chainee copie de env)
	la trie en entier une premiere fois dans une nouvelle liste
	(donc cette fonction est utilisee dans init_export)
	va stocker la sortie dans la structure shell.export
	on supprime la liste chainee export, plus besoin
*/
void	sort_alphabetically(t_list *export)
{
	int swapped;
	int	i;
	t_list *ptr1;
	t_list *lptr;

	if (export == NULL)
		return ;
	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = export;

		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				ft_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}


