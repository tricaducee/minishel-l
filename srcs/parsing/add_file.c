/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:51:22 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/12 15:24:19 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	file_rdi(t_cmdli **cmds_list, char *file)
{
	char	**tmp;

	tmp = (*cmds_list)->file_in;
	(*cmds_list)->file_in = ft_strsjoin(file, tmp);
	if (tmp)
		free(tmp);
	if (!(*cmds_list)->file_in)
		return (error_cmdli(cmds_list, "minishell: memory allocation failed\n"));
	if ((*cmds_list)->here_doc)
	{
		free((*cmds_list)->here_doc);
		(*cmds_list)->here_doc = NULL;
	}
}

void	file_rdo(t_cmdli **cmds_list, char *file, t_type type)
{
	t_file	**tmp;

	tmp = (*cmds_list)->file_out;
	(*cmds_list)->file_out = file_join(file, tmp, type);
	if (tmp)
		free(tmp);
	if (!(*cmds_list)->file_out)
		return (error_cmdli(cmds_list, "minishell: memory allocation failed\n"));
}

void	file_heredoc(t_cmdli **cmds_list, char *file)
{
	if (!(*cmds_list)->pipe_in)
	{
		(*cmds_list)->pipe_in = malloc(2 * sizeof(int));
		if (!(*cmds_list)->pipe_in)
			return (error_cmdli(cmds_list,
					"minishell: memory allocation failed\n"));
		if (pipe((*cmds_list)->pipe_in) == -1)
			return (error_cmdli(cmds_list,
					"minishell: unsuccessful pipe generation\n"));
	}
	(*cmds_list)->here_doc = heredoc(file);
	if (write((*cmds_list)->pipe_in[1],
			(*cmds_list)->here_doc, ft_strlen((*cmds_list)->here_doc)) == -1)
		return (error_cmdli(cmds_list,
				"minishell: unsuccessful pipe writing\n"));
}

void	add_file(t_cmdli **cmds_list, char *file, t_type *type)
{
	if (*type == RDI)
		file_rdi(cmds_list, file);
	else if (*type == RDO)
		file_rdo(cmds_list, file, RDO);
	else if (*type == RDOA)
		file_rdo(cmds_list, file, RDOA);
	else
		file_heredoc(cmds_list, file);
	*type = RFILE;
}
