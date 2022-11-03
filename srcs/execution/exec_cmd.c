/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:15:50 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/03 04:47:17 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

void	get_absolute_path(char *cmd)// char *
{
	char	**path_tab;	

	path_tab = split_path(ft_get_var("PATH"), cmd, ft_strlen(cmd));
	if (!path_tab)
		return /*(ft_strdup(cmd))*/;
	print_tab(path_tab);
}

// void	exec_cmd(t_cmdli *cmdli)
// {
// 	cmdli->cmd = get_absolute_path(cmdli->cmd);
// 	if (!cmdli->cmd)
// 		return ;
// }
