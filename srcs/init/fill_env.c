/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:51:26 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 14:53:19 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	puts each char array (from envp)in a linked list
	care about OLDPWD "declare -x OLDPWD"
*/
// t_list	*fill_env(char **m_env)
// {
// 	// int		i;
// 	// t_list	*env;

// 	// if (m_env == NULL || m_env[i] == NULL)
// 	// 	return (NULL);
// 	// env = NULL;
// 	// i = 0;
// 	// while (m_env[i])
// 	// {
// 	// 	if (env == NULL)
// 	// 		env = ft_lstnew(m_env[i]);
// 	// 	else
// 	// 		ft_lstadd_back(&env, ft_lstnew(m_env[i]));
// 	// 	++i;
// 	// }
// 	// return (env);

// 	printf("salut\n");
// 	return (NULL);
// }

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
		list->content = *(m_env++);
	}
	list->next = NULL;
	return (ret);
}
