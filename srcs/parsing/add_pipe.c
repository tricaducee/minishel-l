/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:55:31 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/17 01:54:20 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	add_pipe(t_cmdli **cmds_list, t_type *type)
{
	*type = PIPE;
	(*cmds_list)->next = create_cmdli();
	if (!(*cmds_list)->next)
		return (error_cmdli(cmds_list, "minishell: memory allocation failed\n"));
	(*cmds_list)->next->previous = (*cmds_list);
	(*cmds_list)->pipe = 1;
	*cmds_list = (*cmds_list)->next;
}

	// (*cmds_list)->next = create_cmdli();
	// if (!(*cmds_list)->next)
	// 	return (error_cmdli(cmds_list, "minishell: memory allocation failed\n"));
	// (*cmds_list)->next->previous = (*cmds_list);
	// if (!(*cmds_list)->pipe_out)
	// 	(*cmds_list)->pipe_out = malloc(2 * sizeof(int));
	// (*cmds_list)->next->pipe_in = (*cmds_list)->pipe_out;
	// *cmds_list = (*cmds_list)->next;
