/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/19 14:38:53 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Dupplicate main environment
*/

char	**ft_strsdup(char **strs)
{
	char			**ret;
	unsigned int	i;

	i = 0;
	while (strs[i])
		i++;
	ret = malloc((i + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		ret[i] = strs[i];
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

// ne pas prendre OLDPWD
char	**init_env_export(char **m_env)
{
	int		len;
	char	**env;

	env = ft_strsdup(m_env);
	int i = 0;
	while (env[i])
	{
		printf("env export : [%s]\n", env[i]);
		++i;
	}
	return (env);
}
