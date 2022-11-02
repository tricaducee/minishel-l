/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_and_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 07:00:28 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/02 02:16:28 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	interpret_func(char *s, t_cmdli **cmds_list, t_type *type, int rd)
{
	if (ft_strcmp_int(s, "<") && !rd)
		*type = RDI;
	else if (ft_strcmp_int(s, "<<") && !rd)
		*type = RDIH;
	else if (ft_strcmp_int(s, ">") && !rd)
		*type = RDO;
	else if (ft_strcmp_int(s, ">>") && !rd)
		*type = RDOA;
	else if (ft_strcmp_int(s, "|")
		&& (*type == CMD || *type == ARG || *type == RFILE))
		add_pipe(cmds_list, type);
	else if (ft_strcmp_int(s, "||")
		&& (*type == CMD || *type == ARG || *type == RFILE))
		add_andor(cmds_list, type, 2);
	else if (ft_strcmp_int(s, "&&")
		&& (*type == CMD || *type == ARG || *type == RFILE))
		add_andor(cmds_list, type, 1);
	else
		return (error_cmdli_interpret(cmds_list, s));
	free(s);
}

void	type_and_set(char *s, t_cmdli **cmds_list, t_type *type, int interpret)
{
	int	rd;

	if (!s)
		return (error_cmdli(cmds_list, "minishell: memory allocation failed\n"));
	if (*type == RDI || *type == RDO || *type == RDIH || *type == RDOA)
		rd = 1;
	else
		rd = 0;
	if (!*cmds_list)
		*cmds_list = create_cmdli();
	if (!*cmds_list)
		return ;
	if (interpret)
		interpret_func(s, cmds_list, type, rd);
	else
	{
		if (*type == CMD || *type == ARG)
			add_arg(cmds_list, s, type);
		else if (!rd)
			add_cmd(cmds_list, s, type);
		else
			add_file(cmds_list, s, type);
	}
}
