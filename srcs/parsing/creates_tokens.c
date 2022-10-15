/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creates_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:03:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/15 23:10:12 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static t_token	*token_new(char *value)
{
	t_token	*token_node;

	token_node = (t_token *)malloc(sizeof(t_token));
	if (!token_node)
		return (NULL);
	token_node->value = value;
	token_node->type = 0;
	token_node->next = NULL;
	return (token_node);
}

static int	create_token(t_token **token_list, char *token_value)
{
	if (!*token_list)
	{
		*token_list = token_new(token_value);
		(*token_list)->previous = NULL;
	}
	else
	{
		while ((*token_list)->next)
			*token_list = (*token_list)->next;
		(*token_list)->next = token_new(token_value);
		(*token_list)->next->previous = *token_list;
		*token_list = (*token_list)->next;
	}
	// type select and check type
	return (0);
}

t_token	*get_token(t_shell *shell)
{
	unsigned int	i;
	unsigned int	j;
	char			*token_value;
	t_token			*token_list;
	t_token			*token_start;

	i = 0;
	token_list = NULL;
	token_start = NULL;
	while (shell->cmdline[i])
	{
		while (shell->cmdline[i] == ' ') //all white space
			++i;
		j = i;
		if (shell->cmdline[j] == '<' || shell->cmdline[j] == '>')
		{
			while (shell->cmdline[j] == '<' || shell->cmdline[j] == '>')
				j++;
			token_value = ft_substr(shell->cmdline, i, j);
			if (!token_value)
				return (NULL); //return exit
			if (create_token(&token_list, token_value))
				return (NULL); //return exit
		}
		else
		{
			while (shell->cmdline[j] && shell->cmdline[j] != ' ')
				j++;
			token_value = ft_substr(shell->cmdline, i, j);
			if (!token_value)
				return (NULL); //return exit
			if (create_token(&token_list, token_value))
				return (NULL); //return exit
		}
	}
	return (token_list);
}