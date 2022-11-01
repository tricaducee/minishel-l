/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 04:27:27 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 04:31:06 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_shell	*ft_get_shell(t_shell *new_shell)
{
	static t_shell	*shell;

	if (new_shell)
		shell = new_shell;
	return (shell);
}
