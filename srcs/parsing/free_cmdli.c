/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmdli.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:39:06 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 06:39:44 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_content(t_cmdli *cmdli)
{
	if (cmdli->cmd)
		free(cmdli->cmd);
	if (cmdli->cmd_args)
		free_tab(cmdli->cmd_args);
	if (cmdli->pipe_in)
	{
		close(cmdli->pipe_in[0]);
		close(cmdli->pipe_in[1]);
		free(cmdli->pipe_in);
	}
	if (cmdli->here_doc)
		free(cmdli->here_doc);
	if (cmdli->file_in)
		free(cmdli->file_in);
	if (cmdli->file_out)
		free(cmdli->file_out);
}

void	free_cmdli(t_cmdli **cmdli)
{
	t_cmdli	*tmp;

	*cmdli = cmdli_first(*cmdli);
	while (*cmdli)
	{
		free_content(*cmdli);
		tmp = *cmdli;
		*cmdli = (*cmdli)->next;
		free(tmp);
	}
}
