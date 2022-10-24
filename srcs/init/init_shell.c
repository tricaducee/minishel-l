/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:49:17 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 18:20:18 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_shell(t_shell *shell, char **m_env)
{
	shell->env = fill_env(m_env);
	shell->export = init_export(shell->env);
	tcgetattr(0, &shell->term);
	shell->sa_interrupt.sa_handler = &handle_interrupt;
	shell->sa_backslash.sa_handler = SIG_IGN;
}

// nouvelle variable sans valeur affichee que dans export