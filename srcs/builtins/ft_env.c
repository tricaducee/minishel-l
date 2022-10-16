/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:12:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/16 15:52:13 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Displays env variables
*/
int	ft_env(t_shell *shell)
{
	t_env	*env_tmp;

	env_tmp = shell->env;
	while (env_tmp)
	{
		printf("%s=%s\n", env_tmp->name, env_tmp->value);
		env_tmp = env_tmp->next;
	}
	return (1);
}
