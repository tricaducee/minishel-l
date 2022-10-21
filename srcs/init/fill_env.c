/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:51:26 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 16:42:43 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Creates new node from main_envs, name and value separated by '='
	m_env : main env variables
	env : list returned, copy of m_env values
	avoid OLDPWD the first time bc we don't have one
*/
// t_env	*fill_env(char **m_env, t_shell *shell)
// {
// 	t_env	*env;
// 	size_t	len;
// 	int		i;

// 	env = NULL;
// 	i = -1;
// 	while (m_env[++i])
// 	{
// 		len = ft_strchr(m_env[i], '=') - m_env[i];
// 		if (ft_strncmp("OLDPWD", m_env[i], 7) == 0)
// 			env_add_back(&env, new_env_node(ft_substr(m_env[i], 0, len), NULL));
// 		else
// 			env_add_back(&env, new_env_node(ft_substr(m_env[i], 0, len), ft_strdup(m_env[i] + len + 1)));
// 	}
// 	return (env);
// }

/*
	puts each char array (from envp)in a linked list
	care about OLDPWD "declare -x OLDPWD"
*/
t_list	*fill_env(char **m_env)
{
	int	i;
	t_list *env;

	if (m_env == NULL || m_env[i] == NULL)
		return (NULL);
	env = NULL;
	i = 0;
	while (m_env[i])
	{
		if (env == NULL)
			ft_lstnew(m_env[i]);
		ft_lstadd_back(&env, ft_lstnew(m_env[i]));
		++i;
	}
	return (env);
}
