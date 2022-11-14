/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:15:50 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/14 00:47:50 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

int	close_pipe(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
	return (0);
}

int	close_and_free(t_cmdli *cmdli)
{
	if (cmdli->pipe_in)
	{
		close(cmdli->pipe_in[0]);
		close(cmdli->pipe_in[1]);
	}
	if (cmdli->cmd)
	{
		free(cmdli->cmd);
		cmdli->cmd = NULL;
	}
	if (cmdli->file_in)
	{
		free_tab(cmdli->file_in);
		cmdli->file_in = NULL;
	}
	if (cmdli->file_out)
	{
		free_file(cmdli->file_out);
		cmdli->file_out = NULL;
	}
	return (0);
}

int	exec_cmd(t_cmdli *cmdli)
{
	cmdli->cmd = get_absolute_path(cmdli->cmd);
	if (!cmdli->cmd)
		return (1);
	cmdli->pid = fork();
	if (cmdli->pid == -1)
	{
		g_errno = errno;
		ft_printfd(2, "#+wminishell#0:#/r %s#0\n", strerror(g_errno));
		return (g_errno);
	}
	else if (!cmdli->pid)
	{
		set_redirection(cmdli);
		if (execve(cmdli->cmd, cmdli->cmd_args, ft_get_str_env()) == -1)
		{
			g_errno = errno;
			ft_printfd(2, "#+wminishell#0: %s: #/r%s#0\n",
				cmdli->cmd_args[0], strerror(g_errno));
			exit(g_errno);
		}
		exit(0);
	}
	else
		return (close_and_free(cmdli));
	return (0);
}
