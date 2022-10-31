/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:57:59 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/31 19:04:07 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	creates our proper list of ENV VAR
	export is made from it
	We avoid OLDPWD, when we open our shell we should not know what was the
	previous directory visited. Gonna be updated in ft_cd builtin.
*/

char	*ft_strldup(char *s, unsigned int len)
{
	char			*ret;
	unsigned int	i;

	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

/*
	initialize list name and list value from char string
	separated by '=' sign
*/
void	split_variable(t_variable *node, char *s)
{
	unsigned int	i;

	i = 0;
	while(s[i] && s[i] != '=')
		i++;
	node->name = ft_strldup(s, i);
	s += i + 1;
	i = 0;
	while(s[i])
		i++;
	node->value = ft_strldup(s, i);
}

/*
	creates new node for t_variable linked list
*/
t_variable	*create_t_variable_node(char *s)
{
	t_variable *node;

	node = (t_variable *)malloc(sizeof(t_variable));
	if (!node)
		return (NULL);
	split_variable(node, s);
	node->next = NULL;
	return (node);
}

t_variable	*init_env(char **m_env)
{
	t_variable	*ret;
	t_variable	*node;

	if (!m_env || !*m_env)
		return (NULL);
	node = create_t_variable_node(*m_env);
	ret = node;
	++m_env;
	while (*m_env)
	{
		if (ft_strncmp(*m_env, "OLDPWD", 6) == 0)
			++m_env;
		node->next = create_t_variable_node(*(m_env++));
		node = node->next;
	}
	node->next = NULL;
	printf("coucou init_env\n");
	return (ret);
}
