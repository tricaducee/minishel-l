/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:12:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/23 16:11:16 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Displays env variables
	The order we see is when items are created
*/
int	ft_env(t_shell *shell)
{
	printlist(shell->env);
	return (1);
}
