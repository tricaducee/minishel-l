/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:12:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 17:14:13 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Displays env variables
	The order we see is when items are created
*/
int	ft_env(t_shell *shell)
{
	t_list	*env_tmp;

	env_tmp = shell->env;
	while (env_tmp)
	{
		printlist(env_tmp);
		env_tmp = env_tmp->next;
	}
	return (1);
}
