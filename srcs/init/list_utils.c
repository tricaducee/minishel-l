/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 17:13:21 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	printlist(t_list *elem)
{
	t_list	*elem_copy;

	elem_copy = elem;
	printf("\n[printlist]\n");
	while (elem_copy)
	{
		printf("[%s]\n", ((char *)elem_copy->content));
		elem_copy = elem_copy->next;
	}
	printf("[end printlist]\n\n");
}

void	print_export(t_list *elem)
{
	t_list	*elem_copy;

	if (elem == NULL)
		return ;
	elem_copy = elem;
	while (elem_copy)
	{
		//trier la liste
		printf("declare -x %s\n", ((char *)elem_copy->content));
		elem_copy = elem_copy->next;
	}
}