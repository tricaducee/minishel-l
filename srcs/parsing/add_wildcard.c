/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 02:51:08 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/08 04:34:54 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*wildcard_ret(char	**cmdline, char *ret,
		unsigned int *i, unsigned int j)
{
	char	*tmp;
	char	*new;

	tmp = ret;
	new = ft_substr(*cmdline, *i, j);
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
	return (ret);
}

char	*wildcard_add_func(char **cmdline, char *ret, unsigned int *i)
{
	if ((*cmdline)[*i] && (*cmdline)[*i] == '*')
	{
		(*i)++;
		if (!ret)
			ret = ft_strdup("");
		return (check_and_get_wildcard(ret));
	}
	else if ((*cmdline)[*i] && (*cmdline)[*i] == '$')
		return (add_var(cmdline, ret, i));
	else if ((*cmdline)[*i] && (*cmdline)[*i] == '\'')
		return (add_quote(cmdline, ret, i));
	else if ((*cmdline)[*i] && (*cmdline)[*i] == '"')
		return (add_dquote(cmdline, ret, i));
	return (ret);
}

char	*add_wildcard(char **cmdline, char *ret, unsigned int *i)
{
	unsigned int	j;

	check_and_get_wildcard(ret);
	(*i)++;
	ret = NULL;
	while ((*cmdline)[*i] && (*cmdline)[*i] != ' ' && (*cmdline)[*i]
		!= '<' && (*cmdline)[*i] != '>' && (*cmdline)[*i]
		!= '|' && (*cmdline)[*i] != '&')
	{
		j = 0;
		while ((*cmdline)[*i + j] && (*cmdline)[*i + j] != '$'
			&& (*cmdline)[*i + j] != ' ' && (*cmdline)[*i + j]
			!= '<' && (*cmdline)[*i + j] != '>' && (*cmdline)[*i + j]
			!= '|' && (*cmdline)[*i + j] != '&' && (*cmdline)[*i + j]
			!= '\'' && (*cmdline)[*i + j] != '"' && (*cmdline)[*i + j] != '*')
			++j;
		if (j)
			ret = wildcard_ret(cmdline, ret, i, j);
		*i += j;
		ret = wildcard_add_func(cmdline, ret, i);
	}
	return (ret);
}
