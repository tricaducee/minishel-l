/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:58:28 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 06:59:18 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*add_dquote(char *(*cmdline), char *str, unsigned int *i)
{
	char			*ret;
	unsigned int	j;
	char			*tmp;
	char			*new;

	++*i;
	ret = str;
	while ((*cmdline)[*i] && (*cmdline)[*i] != '"')
	{
		j = 0;
		while ((*cmdline)[*i + j] && (*cmdline)[*i + j]
			!= '"' && (*cmdline)[*i + j] != '$')
			j++;
		tmp = ret;
		new = ft_substr((*cmdline), *i, j);
		if (!new)
		{
			if (tmp)
				free(tmp);
			return (NULL);
		}
		ret = ft_strjoin(tmp, new);
		free(new);
		if (tmp)
			free(tmp);
		if (!ret)
			return (NULL);
		*i += j;
		if ((*cmdline)[*i] && (*cmdline)[*i] == '$')
			ret = add_var(cmdline, ret, i);
	}
	++*i;
	return (ret);
}
