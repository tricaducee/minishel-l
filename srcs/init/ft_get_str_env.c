/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_str_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:20:33 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/11/03 09:25:44 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**ft_get_str_env(void)
{
	t_shell	*shell;

	shell = ft_get_shell(NULL);
	return (shell->str_env);
}
