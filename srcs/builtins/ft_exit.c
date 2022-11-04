/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:25:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/04 03:23:39 by hrolle           ###   ########.fr       */
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
