/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:15:50 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/03 23:51:02 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

unsigned int	path_counter(char *path)
{
	unsigned int	count;

	count = 0;
	while (*path)
	{
		if (*path && *path != ':' && (!*(path + 1) || *(path + 1) == ':'))
			count++;
		path++;
	}
	return (count);
}

char	*path_join(char *path, char *cmd,
				unsigned int path_len, unsigned int cmd_len)
{
	char			*ret;
	unsigned int	i;

	ret = malloc((path_len + cmd_len + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < path_len)
		ret[i++] = *(path++);
	ret[i++] = '/';
	while (*cmd)
		ret[i++] = *(cmd++);
	ret[i] = 0;
	return (ret);
}

char	**split_path(char *path, char *cmd, unsigned int cmd_len)
{
	char			**ret;
	unsigned int	i;
	unsigned int	j;

	ret = malloc((path_counter(path) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	while (*path)
	{
		while (*path == ':')
			path++;
		i = 0;
		while (path[i] && path[i] != ':')
			i++;
		ret[j] = path_join(path, cmd, i, cmd_len);
		if (!ret[j++])
			return (free_tab_null(ret));
		path += i;
	}
	ret[j] = NULL;
	return (ret);
}

char	*get_absolute_path(char *cmd)
{
	char			**path_tab;
	char			*ret;
	unsigned int	i;

	if (ft_strchr((const char *)cmd, '/'))
		return (ft_strdup(cmd));
	path_tab = split_path(ft_get_var("PATH"), cmd, ft_strlen(cmd));
	if (!path_tab)
		return (ft_strdup(cmd));
	i = 0;
	while (path_tab[i] && access(path_tab[i], X_OK) == -1)
		i++;
	if (!path_tab[i])
	{
		g_errno = errno;
		ft_printfd(2, "#+wminishell#0: #/r%s#0\n", strerror(g_errno));
		return (NULL);
	}
	ret = ft_strdup(path_tab[i]);
	free_tab(path_tab);
	return (ret);
}

int	exec_cmd(t_cmdli *cmdli)//here_doc se comporte comme un fichier
{
	unsigned int	i;

	cmdli->cmd = get_absolute_path(cmdli->cmd);
	if (!cmdli->cmd)
		exit(1);
	cmdli->pid = fork();
	if (cmdli->pid == -1)
	{
		g_errno = errno;
		ft_printfd(2, "#+wminishell#0:#/r %s#0", strerror(g_errno));
		exit(g_errno);
	}
	else if (!cmdli->pid)
	{
		if (cmdli->pipe_in)
			close(cmdli->pipe_in[1]);
		if (cmdli->pipe_out)
			close(cmdli->pipe_out[0]);
		if (cmdli->file_in)
		{
			i = 0;
			while (cmdli->file_in[i])
			{
				if (cmdli->fd_in != -1)
					close(cmdli->fd_in);
				cmdli->fd_in = open(cmdli->file_in[i++], O_RDONLY);
				if (cmdli->fd_in == -1)
				{
					g_errno = errno;
					ft_printfd(2, "#+wminishell#0:#/r %s#0", strerror(g_errno));
					exit(g_errno);
				}
			}
		}
		if (cmdli->file_out)
		{
			i = 0;
			while (cmdli->file_out[i])
			{
				if (cmdli->fd_out != -1)
					close(cmdli->fd_out);
				if (cmdli->file_type == RDO)
					cmdli->fd_out = open(cmdli->file_out[i++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (cmdli->file_type == RDOA)
					cmdli->fd_out = open(cmdli->file_out[i++], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (cmdli->fd_out == -1)
				{
					g_errno = errno;
					ft_printfd(2, "#+wminishell#0:#/r %s#0", strerror(g_errno));
					exit(g_errno);
				}
			}
		}
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
		if (execve(cmdli->cmd, cmdli->cmd_args, ft_get_str_env()) == -1)
		{
			g_errno = errno;
			ft_printfd(2, "#+wminishell#0: #/r%s#0\n", strerror(g_errno));
			exit(g_errno);
		}
		exit(0);
	}
	else
	{
		if (cmdli->pipe_in)
		{
			close(cmdli->pipe_in[0]);
			close(cmdli->pipe_in[1]);
			//free(cmdli->pipe_in);
			//cmdli->pipe_in = NULL;
		}
		// if (cmdli->pipe_out)
		// {
			// close(cmdli->pipe_out[0]);
			// close(cmdli->pipe_out[1]);
			////free(cmdli->pipe_out);
			////cmdli->pipe_out = NULL;
		// }
		return (0);
	}
	return (0);
}
