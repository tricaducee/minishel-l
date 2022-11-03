/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 01:09:41 by lgenevey         ###   ########.fr       */
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

void	sort_alpha(t_variable *export, t_variable *new)
{
	t_variable	*prev;
	static int	i;

	prev = NULL;
	i++;
	//ft_printfd(1, "new %d : [%s]\n", i, new->name);
	ft_printfd(1, "#+rexport %d : [%s]#0\n", i, export->name);
	while (export)
	{
		if (ft_strcmp(export->name, new->name) >= 0)
		{
			if (prev)
				prev->next = new;
			new->next = export;
			ft_printfd(1, "while : new->next %d : [%s]\n", i, new->next->name);
			if (prev)
				ft_printfd(1, "#+gwhile : prev->next %d : [%s]\n#0", i, prev->next->name);
			else
				ft_printfd(1, "#+gwhile : prev->next %d : [%s]\n#0", i, new->name);
			return ;
		}
		prev = export;
		export = export->next;
	}
	if (!export)
	{
		prev->next = new;
		ft_printfd(1, "new->next %d : [%p]\n", i, new->next);
		ft_printfd(1, "#+gprev->next %d : [%s]\n#0", i, prev->next->name);
	}
}
