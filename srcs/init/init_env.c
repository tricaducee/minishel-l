//
// Created by Hajar Sabir on 10/12/22.
//

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
*/
t_env	*init_env(char **main_envs)
{
	t_env	*env;
	size_t	len;
	int		i;

	env = NULL;
	i = -1;
	while (main_envs[++i])
	{
		len = ft_strchr(main_envs[i], '=') - main_envs[i];
		if (ft_strncmp("OLDPWD", main_envs[i], 7) == 0)
			env_add_back(&env, new_env_node(ft_substr(main_envs[i], 0, len), NULL));
		else
			env_add_back(&env, new_env_node(ft_substr(main_envs[i], 0, len),
										ft_strdup(main_envs[i] + len + 1)));
	}
	return (env);
}