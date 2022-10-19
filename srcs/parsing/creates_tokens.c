/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creates_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:03:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/19 16:50:40 by lgenevey         ###   ########.fr       */
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
		printf("create_token 1\n");
		*token_list = token_new(token_value);
		printf("token node : %s\n", (*token_list)->value);
		(*token_list)->previous = NULL;
	}
	else
	{
		printf("create_token 2\n");
		while ((*token_list)->next)
		{
			//printf("token node : %s\n", (*token_list)->value);
			*token_list = (*token_list)->next;
		}
		(*token_list)->next = token_new(token_value);
		(*token_list)->next->previous = *token_list;
		*token_list = (*token_list)->next;
		printf("token node : %s\n", (*token_list)->value);
	}
	// type select and check type
	return (0);
}

/*
	reads string got by readline() char per char
	if char is 'special' : treat it in its special way
	if not special, split string to get a char** with pieces of cmdline
	if double quote ne pas interpreter l'interieur
	bash-3.2$ echo '"$PATH"'
"	$PATH"
	bash-3.2$ echo "'$PATH'"
	'/Users/lgenevey/.brew/bin:/Users/lgenevey/.nvm/versions/node/v16.14.0/bin:/Users/lgenevey/.brew/bin:/Users/lgenevey/.nvm/versions/node/v16.14.0/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/lgenevey/.brew/bin:/Users/lgenevey/.nvm/versions/node/v16.14.0/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin'
*/
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
		j = 0;
		if (shell->cmdline[i + j] == '<' || shell->cmdline[i + j] == '>')
		{
			while (shell->cmdline[i + j] == '<' || shell->cmdline[i + j] == '>')
				j++;
			token_value = ft_substr(shell->cmdline, i, j);
			if (!token_value)
				return (NULL); //return exit
			if (create_token(&token_list, token_value))
				return (NULL); //return exit
		}
		else
		{
			while (shell->cmdline[i + j] && shell->cmdline[i + j] != ' ' && shell->cmdline[i + j] != '<' && shell->cmdline[i + j] != '>')
				j++;
			token_value = ft_substr(shell->cmdline, i, j);
			//token_value = ft_strldup(shell->cmdline + i, j);
			if (!token_value)
				return (NULL); //return exit
			if (create_token(&token_list, token_value))
				return (NULL); //return exit
			while (token_list->previous)
				token_list = token_list->previous;
		}
		i += j;
	}
	return (token_list);
}