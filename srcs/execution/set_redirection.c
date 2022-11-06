/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:10:11 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/06 13:20:07 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

void	set_file_in(t_cmdli *cmdli)
{
	unsigned int	i;

	i = 0;
	while (cmdli->file_in[i])
	{
		if (cmdli->fd_in != -1)
			close(cmdli->fd_in);
		cmdli->fd_in = open(cmdli->file_in[i++], O_RDONLY);
		if (cmdli->fd_in == -1)
		{
			g_errno = errno;
			ft_printfd(2, "#+wminishell#0: %s:#/r %s#0\n",
				cmdli->file_in[i - 1], strerror(g_errno));
		}
	}
}

void	set_file_out(t_cmdli *cmdli)
{
	unsigned int	i;

	i = 0;
	while (cmdli->file_out[i])
	{
		if (cmdli->fd_out != -1)
			close(cmdli->fd_out);
		if (cmdli->file_type == RDO)
			cmdli->fd_out = open(cmdli->file_out[i++],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (cmdli->file_type == RDOA)
			cmdli->fd_out = open(cmdli->file_out[i++],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmdli->fd_out == -1)
		{
			g_errno = errno;
			ft_printfd(2, "#+wminishell#0: %s:#/r %s#0\n",
				cmdli->file_out[i - 1], strerror(g_errno));
		}
	}
}

void	set_in(t_cmdli *cmdli)
{
	if (cmdli->fd_in != -1 && !cmdli->here_doc)
	{
		dup2(cmdli->fd_in, STDIN_FILENO);
		close(cmdli->fd_in);
		if (cmdli->pipe_in)
			close(cmdli->pipe_in[0]);
	}
	else if (cmdli->pipe_in)
	{
		dup2(cmdli->pipe_in[0], STDIN_FILENO);
		close(cmdli->pipe_in[0]);
	}
}

void	set_out(t_cmdli *cmdli)
{
	if (cmdli->fd_out != -1)
	{
		dup2(cmdli->fd_out, STDOUT_FILENO);
		close(cmdli->fd_out);
		if (cmdli->pipe_out)
			close(cmdli->pipe_out[1]);
	}
	else if (cmdli->pipe_out)
	{
		dup2(cmdli->pipe_out[1], STDOUT_FILENO);
		close(cmdli->pipe_out[1]);
	}
}

void	set_redirection(t_cmdli *cmdli)
{
	if (cmdli->pipe_in)
		close(cmdli->pipe_in[1]);
	if (cmdli->pipe_out)
		close(cmdli->pipe_out[0]);
	if (cmdli->file_in)
		set_file_in(cmdli);
	if (cmdli->file_out)
		set_file_out(cmdli);
	set_in(cmdli);
	set_out(cmdli);
}
