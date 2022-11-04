/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:15:50 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/04 09:02:01 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

int	close_pipe(int	*pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
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
		ft_printfd(2, "#+wminishell#0:#/r %s#0", strerror(g_errno));
		return (g_errno);
	}
	else if (!cmdli->pid)
	{
		set_redirection(cmdli);
		if (execve(cmdli->cmd, cmdli->cmd_args, ft_get_str_env()) == -1)
		{
			g_errno = errno;
			ft_printfd(2, "#+wminishell#0: #/r%s#0\n", strerror(g_errno));
			exit(g_errno);
		}
		exit(0);
	}
	else
		return (close_pipe(cmdli->pipe_in));
	return (0);
}
