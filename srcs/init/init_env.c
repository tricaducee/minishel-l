/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:57:59 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/29 15:57:15 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	creates our proper list of ENV VAR
	export is made from it
	We avoid OLDPWD, when we open our shell we should not know what was the
	previous directory visited. Gonna be updated in ft_cd builtin.
*/
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
		if (ft_strncmp(*m_env, "OLDPWD", 6) == 0)
			++m_env;
		list->next = malloc(sizeof(t_list));
		if (!list->next)
			return (NULL);
		list = list->next;
		list->content = ft_strdup(*(m_env++));
	}
	list->next = NULL;
	return (ret);
}
