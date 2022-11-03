/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 01:17:32 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 01:19:30 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../incs/minishell.h"

t_variable	*ft_get_env(void)
{
	t_shell	*shell;

	shell = ft_get_shell(NULL);
	return (shell->env);
}
