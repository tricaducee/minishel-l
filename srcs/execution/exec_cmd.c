/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:15:50 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/17 02:03:47 by hermesrolle      ###   ########.fr       */
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

int	write_heredoc(t_cmdli *cmdli)
{
	if (!cmdli->here_doc)
		return (0);
	if (!cmdli->pipe_in)
	{
		cmdli->pipe_in = malloc(2 * sizeof(int));
		if (!cmdli->pipe_in)
			return (return_error("59 at exec_cmd.c"));
		if (pipe(cmdli->pipe_in) == -1)
			return (return_error("61 at exec_cmd.c"));
	}
	else
	{
		close_pipe(cmdli->pipe_in);
	}
	if (write(cmdli->pipe_in[1],
			cmdli->here_doc, ft_strlen(cmdli->here_doc)) == -1)
		return (return_error("69 at exec_cmd.c"));
	return (0);
}

int	set_cmd(t_cmdli *cmdli)
{
	cmdli->cmd = get_absolute_path(cmdli->cmd, ft_get_var("PATH"));
	if (!cmdli->cmd)
		return (1);
	if (write_heredoc(cmdli))
		return (1);
	if (!cmdli->pipe)
		return (0);
	cmdli->pipe_out = malloc(2 * sizeof(int));
	if (!cmdli->pipe_out)
		return (return_error("84 at exec_cmd.c"));
	if (pipe(cmdli->pipe_out) == -1)//-------------------malloc pipe here
		return (return_error("86 at exec_cmd.c"));
	cmdli->next->pipe_in = cmdli->pipe_out;
	return (0);
}

int	exec_cmd(t_cmdli *cmdli)
{
	if (set_cmd(cmdli))
		return (1);
	cmdli->pid = fork();
	if (cmdli->pid == -1)
		return (return_error("97 at exec_cmd.c"));
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
	}
	else
		ft_get_shell(NULL)->if_sig = 0;
	return (close_and_free(cmdli));
}
