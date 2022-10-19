/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:25:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/18 18:39:07 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_envs(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		env->name = NULL;
		if (env->value)
			free(env->value);
		env->value = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}


//valeurs de sortie et recuperer le numero de largument si il y a
//attention + et - de 256
void	ft_exit(t_shell *shell)
{
	free(shell->cmdline);
	//free(shell->prompt);
	//shell->prompt = NULL;
	free_envs(shell->env);
	shell->env = NULL;
	ft_putendl_fd("exit", 1);
	//rl_clear_history();
	exit(0);
}