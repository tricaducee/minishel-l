/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:43:55 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/05 07:39:13 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*split_cmd(char *(*cmdline), unsigned int *i, char c)
{
	unsigned int	j;

	j = 0;
	while ((*cmdline)[*i + j] && ((*cmdline)[*i + j] == c))
		++j;
	*i += j;
	return (ft_substr((*cmdline), *i - j, j));
}

char	*split_cmd_sp_ret(char	**cmdline, char *ret,
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

char	*split_cmd_sp_add_func(char **cmdline, char *ret, unsigned int *i)
{
	if ((*cmdline)[*i] && (*cmdline)[*i] == '$')
		return (add_var(cmdline, ret, i));
	else if ((*cmdline)[*i] && (*cmdline)[*i] == '\'')
		return (add_quote(cmdline, ret, i));
	else if ((*cmdline)[*i] && (*cmdline)[*i] == '"')
		return (add_dquote(cmdline, ret, i));
	return (ret);
}

char	*split_cmd_sp(char **cmdline, unsigned int *i)
{
	unsigned int	j;
	char			*ret;

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
			ret = split_cmd_sp_ret(cmdline, ret, i, j);
		*i += j;
		ret = split_cmd_sp_add_func(cmdline, ret, i);
	}
	return (ret);
}

// char	*split_cmd_sp(char **cmdline, unsigned int *i)
// {
// 	unsigned int	j;
// 	char			*ret;
// 	char			*tmp;
// 	char			*new;

// 	ret = NULL;
// 	while ((*cmdline)[*i] && (*cmdline)[*i] != ' ' && (*cmdline)[*i]
// 		!= '<' && (*cmdline)[*i] != '>' && (*cmdline)[*i]
// 		!= '|' && (*cmdline)[*i] != '&')
// 	{
// 		j = 0;
// 		while ((*cmdline)[*i + j] && (*cmdline)[*i + j] != '$'
// 			&& (*cmdline)[*i + j] != ' ' && (*cmdline)[*i + j]
// 			!= '<' && (*cmdline)[*i + j] != '>' && (*cmdline)[*i + j]
// 			!= '|' && (*cmdline)[*i + j] != '&' && (*cmdline)[*i + j]
// 			!= '\'' && (*cmdline)[*i + j] != '"')
// 			++j;
// 		if (j)
// 		{
// 			tmp = ret;
// 			new = ft_substr(*cmdline, *i, j);
// 			if (!new)
// 			{
// 				if (tmp)
// 					free(tmp);
// 				return (NULL);
// 			}
// 			ret = ft_strjoin(tmp, new);
// 			free(new);
// 			if (tmp)
// 				free(tmp);
// 			if (!ret)
// 				return (NULL);
// 			tmp = NULL;
// 		}
// 		*i += j;
// 		if ((*cmdline)[*i] && (*cmdline)[*i] == '$')
// 			ret = add_var(cmdline, ret, i);
// 		else if ((*cmdline)[*i] && (*cmdline)[*i] == '\'')
// 			ret = add_quote(cmdline, ret, i);
// 		else if ((*cmdline)[*i] && (*cmdline)[*i] == '"')
// 			ret = add_dquote(cmdline, ret, i);
// 	}
// 	return (ret);
// }
