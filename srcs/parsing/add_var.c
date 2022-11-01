/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 07:00:06 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 07:00:50 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

#include "../../incs/minishell.h"

char	*add_var(char *(*cmdline), char *str, unsigned int *i)
{
	char			*ret;
	unsigned int	j;
	char			*tmp;
	char			*new;

	j = 0;
	++*i;
	ret = NULL;
	while ((*cmdline)[*i + j] && (*cmdline)[*i + j] != '$' && (*cmdline)[*i + j]
		!= ' ' && (*cmdline)[*i + j] != '<' && (*cmdline)[*i + j]
		!= '>' && (*cmdline)[*i + j] != '|' && (*cmdline)[*i + j]
		!= '&' && (*cmdline)[*i + j] != '\'' && (*cmdline)[*i + j] != '"')
		j++;
	if (j)
		new = ft_get_var(ft_substr((*cmdline), *i, j));
	else if ((*cmdline)[*i] != '"' && (*cmdline)[*i] != '\'')
		new = ft_strdup("$");
	else
		new = ft_strdup("");
	tmp = str;
	if (!new)
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	ret = ft_strjoin(str, new);
	free(new);
	if (tmp)
		free(tmp);
	if (!ret)
		return (NULL);
	*i += j;
	return (ret);
}
