/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:51:26 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/23 16:26:41 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	puts each char array (from envp)in a linked list
	care about OLDPWD "declare -x OLDPWD"
*/
t_list	*fill_env(char **m_env)
{
	int		i;
	t_list	*env;

	if (m_env == NULL || m_env[i] == NULL)
		return (NULL);
	env = NULL;
	i = 0;
	while (m_env[i])
	{
		if (env == NULL)
			env = ft_lstnew(m_env[i]);
		else
			ft_lstadd_back(&env, ft_lstnew(m_env[i]));
		++i;
	}
	return (env);
}
