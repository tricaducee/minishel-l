/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdli_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:36:12 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/15 06:00:29 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmdli	*cmdli_first(t_cmdli *cmds_list)
{
	if (!cmds_list)
		return (NULL);
	while (cmds_list->previous)
		cmds_list = cmds_list->previous;
	return (cmds_list);
}
