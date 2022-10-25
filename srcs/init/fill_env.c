/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:51:26 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/25 20:59:44 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_list	*fill_env(char **m_env)
{
	t_list	*ret;
	t_list	*list;

	if (!m_env || !*m_env)
		return (NULL);
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = *(m_env++);
	ret = list;
	while (*m_env)
	{
		list->next = malloc(sizeof(t_list));
		if (!list->next)
			return (NULL);
		list = list->next;
		list->content = ft_strdup(*(m_env++));
	}
	list->next = NULL;
	return (ret);
}
