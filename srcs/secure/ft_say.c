/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_say.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:45:28 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/15 05:32:58 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_say(char *str)
{
	char	**strs;
	char	*path;
	int		pid;

	strs = malloc(3 * sizeof(char *));
	if (!strs)
		return ;
	strs[0] = ft_strdup("say");
	strs[1] = ft_strdup(str);
	strs[2] = NULL;
	path = get_absolute_path("say", ft_get_var("PATH"));
	if (!path)
	{
		free_tab(strs);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
		execve(path, strs, ft_get_str_env());
	free(path);
	free_tab(strs);
}
