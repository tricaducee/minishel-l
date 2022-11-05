/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:25:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/05 03:51:30 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	ft_exit(t_shell *shell, t_cmdli **cmdli, char *read)
{
	free_nodes_contents(&shell->export);
	free_nodes(&shell->env);
	free_cmdli(cmdli);
	free(read);
	return (g_errno);
}

// verifier si nombre, si oui faire atoi, si pas nombre exit 0