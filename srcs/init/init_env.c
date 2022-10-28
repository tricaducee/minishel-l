/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:57:59 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/28 00:22:46 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_list	*init_env(char **m_env)
{
	t_list	*ret;
	t_list	*list;

	if (!m_env || !*m_env)
		return (NULL);
	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = ft_strdup(*(m_env++));
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
