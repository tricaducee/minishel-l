/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:12:23 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/05 02:22:38 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

char	**free_path(char **tab, char *path)
{
	if (tab)
		free_tab(tab);
	if (path)
		free(path);
	return (NULL);
}

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
	char			*path_i;
	unsigned int	i;
	unsigned int	j;

	path_i = path;
	ret = malloc((path_counter(path) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	while (*path_i)
	{
		while (*path_i == ':')
			path_i++;
		i = 0;
		while (path_i[i] && path_i[i] != ':')
			i++;
		ret[j] = path_join(path_i, cmd, i, cmd_len);
		if (!ret[j++])
			return (free_path(ret, path));
		path_i += i;
	}
	free_path(NULL, path);
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
		free_tab(path_tab);
		g_errno = errno;
		ft_printfd(2, "#+wminishell#0: #/r%s#0\n", strerror(g_errno));
		return (NULL);
	}
	ret = ft_strdup(path_tab[i]);
	free_tab(path_tab);
	return (ret);
}
