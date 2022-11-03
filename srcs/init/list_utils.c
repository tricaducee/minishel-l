/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 02:40:54 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

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
	(used for current linked list)
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

void	sort_alpha(t_variable **export, t_variable *new)
{
	t_variable	*prev;
	t_variable	*current;
	static int	i;

	prev = NULL;
	current = *export;
	i++;
	while (current)
	{
		if (ft_strcmp(current->name, new->name) >= 0)
		{
			if (prev)
				prev->next = new;
			else
				(*export) = new;
			new->next = current;
			return ;
		}
		prev = current;
		current = current->next;
	}
	if (!current)
		prev->next = new;
}

// void	sort_alpha(t_variable *current, t_variable *new)
// {
// 	t_variable	*prev;
// 	static int	i;

// 	prev = NULL;
// 	i++;
// 	//ft_printfd(1, "new %d : [%s]\n", i, new->name);
// 	ft_printfd(1, "#+rcurrent %d : [%s]#0\n", i, current->name);
// 	while (current)
// 	{
// 		if (ft_strcmp(current->name, new->name) >= 0)
// 		{
// 			if (prev)
// 				prev->next = new;
// 			new->next = current;
// 			ft_printfd(1, "while : new->next %d : [%s]\n", i, new->next->name);
// 			if (prev)
// 				ft_printfd(1, "#+gwhile : prev->next %d : [%s]\n#0", i, prev->next->name);
// 			else
// 				ft_printfd(1, "#+gwhile : prev->next %d : [%s]\n#0", i, new->name);
// 			return ;
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// 	if (!current)
// 	{
// 		prev->next = new;
// 		ft_printfd(1, "new->next %d : [%p]\n", i, new->next);
// 		ft_printfd(1, "#+gprev->next %d : [%s]\n#0", i, prev->next->name);
// 	}
// }
