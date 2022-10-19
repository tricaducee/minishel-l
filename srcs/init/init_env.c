/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:51:26 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/18 17:53:36 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static t_env	*get_last_env(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

static t_env	*new_env_node(char	*name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

static void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		ptr = get_last_env(*lst);
		ptr->next = new;
	}
}

/*
	Creates new node from main_envs, name and value separated by '='
	m_env : main env variables
	env : list returned, copy of m_env values
*/
t_env	*init_env(char **m_env)
{
	t_env	*env;
	size_t	len;
	int		i;

	env = NULL;
	i = -1;
	while (m_env[++i])
	{
		len = ft_strchr(m_env[i], '=') - m_env[i];
		if (ft_strncmp("OLDPWD", m_env[i], 7) == 0)
			env_add_back(&env, new_env_node(ft_substr(m_env[i], 0, len), NULL));
		else
			env_add_back(&env, new_env_node(ft_substr(m_env[i], 0, len),
										ft_strdup(m_env[i] + len + 1)));
	}
	return (env);
}
