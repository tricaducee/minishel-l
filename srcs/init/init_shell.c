/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:49:17 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 09:24:34 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_shell(t_shell *shell, char **m_env)
{
	shell->env = init_env(m_env);
	shell->export = init_export();
	shell->str_env = m_env;
	tcgetattr(0, &shell->term);
	shell->sa_interrupt.sa_handler = &handle_interrupt;
	shell->sa_backslash.sa_handler = SIG_IGN;
}

// nouvelle variable sans valeur affichee que dans export