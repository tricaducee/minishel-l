/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/28 01:05:16 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print a list from a copy pointer
*/
void	printlist(t_list *top)
{
	t_list	*elem_copy;

	elem_copy = top;
	while (elem_copy)
	{
		printf("%s\n", ((char *)elem_copy->content));
		elem_copy = elem_copy->next;
	}
}

void ft_swap(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

/*
	Bubble sort : sort export linked list for initialization.
*/
void	sort_alphabetically(t_list *export)
{
	int swapped;
	int	i;
	t_list *env1;
	t_list *lenv;

	if (export == NULL)
		return ;
	swapped = 1;
	lenv = NULL;
	while (swapped)
	{
		swapped = 0;
		env1 = export;

		while (env1->next != lenv)
		{
			if (ft_strcmp(env1->content, env1->next->content) > 0)
			{
				ft_swap(env1, env1->next);
				swapped = 1;
			}
			env1 = env1->next;
		}
		lenv = env1;
	}
}

/*
	returns value of ENV VAR name searched
	env : first node of our linked list of every ENV VAR
	substr : name of the variable whose value we want.
*/
char	*ft_get_env(t_list *env, char *substr)
{
	char	*ret;
	size_t	from;
	size_t	to;

	if (!env || !substr)
		return (NULL);
	if (!ft_strcmp(substr, "?")) //gestion de errno
		return (ft_itoa(errnum));
	ret = NULL;
	while (env)
	{
		from = (ft_strchr(env->content, '=') - (char *)env->content) + 1;
		to = ft_strlen(substr);
		if (ft_strncmp(substr, env->content, to) == 0)
			ret = ft_substr(env->content, from, to - from);
		env = env->next;
	}
	if (!ret)
		return (ft_strdup(""));
	return (ret);
}
