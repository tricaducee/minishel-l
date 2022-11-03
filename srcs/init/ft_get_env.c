/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 01:17:32 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 01:43:54 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_variable	*ft_get_env(void)
{
	t_shell	*shell;

	shell = ft_get_shell(NULL);
	return (shell->env);
}
