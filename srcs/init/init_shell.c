/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:49:17 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/15 02:34:16 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_shell(t_shell *shell, char **m_env)
{
	shell->env = init_env(m_env);
	shell->export = init_export();
	shell->str_env = m_env;
	shell->if_sig = 1;
	shell->sa_interrupt.sa_handler = &handle_interrupt;
	shell->sa_backslash.sa_handler = SIG_IGN;
}
