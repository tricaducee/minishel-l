/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:49:17 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 16:39:58 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_shell(t_shell *shell, char **m_env)
{
	shell->cmdline = NULL;
	shell->cmd = NULL;
	shell->env = fill_env(m_env);
	shell->export = fill_export(shell->env);
	shell->std_in = 0;
	shell->std_out = 0;
	tcgetattr(0, &shell->term);
	shell->sa_interrupt.sa_handler = &handle_interrupt;
	shell->sa_backslash.sa_handler = SIG_IGN;
}

// nouvelle variable sans valeur affichee que dans export