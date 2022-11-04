/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_dquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:58:28 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/04 08:46:33 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*add_dquote_ret(char **cmdline, char *ret, char **tmp, unsigned int *i)
{
	unsigned int	j;
	char			*new;

	j = 0;
	while ((*cmdline)[*i + j] && (*cmdline)[*i + j]
		!= '"' && (*cmdline)[*i + j] != '$')
		j++;
	*tmp = ret;
	new = ft_substr((*cmdline), *i, j);
	if (!new)
		return (NULL);
	ret = ft_strjoin(*tmp, new);
	free(new);
	if (!ret)
		return (NULL);
	*i += j;
	if ((*cmdline)[*i] && (*cmdline)[*i] == '$')
		ret = add_var(cmdline, ret, i);
	return (ret);
}

char	*add_dquote(char **cmdline, char *str, unsigned int *i)
{
	char			*ret;
	char			*tmp;

	++*i;
	ret = str;
	while ((*cmdline)[*i] && (*cmdline)[*i] != '"')
	{
		ret = add_dquote_ret(cmdline, ret, &tmp, i);
		if (tmp)
			free(tmp);
		if (!ret)
			return (NULL);
	}
	++*i;
	if (!ret)
		return (ft_strdup(""));
	return (ret);
}

// char	*add_dquote(char **cmdline, char *str, unsigned int *i)
// {
// 	char			*ret;
// 	unsigned int	j;
// 	char			**tmp;
// 	char			*new;

// 	++*i;
// 	ret = str;
// 	while ((*cmdline)[*i] && (*cmdline)[*i] != '"')
// 	{
// 		j = 0;
// 		while ((*cmdline)[*i + j] && (*cmdline)[*i + j]
// 			!= '"' && (*cmdline)[*i + j] != '$')
// 			j++;
// 		*tmp = ret;
// 		new = ft_substr((*cmdline), *i, j);
// 		if (!new)
// 		{
// 			if (*tmp)
// 				free(*tmp);
// 			return (NULL);
// 		}
// 		ret = ft_strjoin(*tmp, new);
// 		free(new);
// 		if (*tmp)
// 			free(*tmp);
// 		if (!ret)
// 			return (NULL);
// 		*i += j;
// 		if ((*cmdline)[*i] && (*cmdline)[*i] == '$')
// 			ret = add_var(cmdline, ret, i);
// 	}
// 	++*i;
// 	return (ret);
// }
