/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:55:17 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 06:57:38 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	add_arg(t_cmdli **cmds_list, char *arg, t_type *type)
{
	char	**tmp;

	*type = ARG;
	tmp = (*cmds_list)->cmd_args;
	(*cmds_list)->cmd_args = ft_strsjoin(arg, tmp);
	if (tmp)
		free(tmp);
	if (!(*cmds_list)->cmd_args)
		return (error_cmdli(cmds_list, "minishell: memory allocation failed\n"));
}
