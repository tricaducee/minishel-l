/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:32:22 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/25 23:05:31 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_strjoin_nl(char *s1, char *s2)
{
	char	*str;
	char	*ret;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	ret = str;
	if (!str)
		return (0);
	while (s1 && *s1)
		*(str++) = *(s1++);
	while (s2 && *s2)
		*(str++) = *(s2++);
	*(str++) = '\n';
	*str = 0;
	return (ret);
}

char	*heredoc(char *limit)
{
	char	*line;
	char	*ret;
	char	*tmp;

	ret = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, limit))
		{
			tmp = ret;
			ret = ft_strjoin_nl(tmp, line);
			free(tmp);
			free(line);
		}
		else
		{
			free(line);
			break ;
		}
	}
	free(limit);
	return (ret);
}
