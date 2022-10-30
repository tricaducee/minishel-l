/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/30 13:53:16 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print a list from a copy pointer
*/
void	printlist(t_variable *top)
{
	t_variable	*elem_copy;

	elem_copy = top;
	while (elem_copy)
	{
		printf("%s=%s\n", elem_copy->name, elem_copy->value);
		elem_copy = elem_copy->next;
	}
}

/*
	tri par insertion a la place
*/
void ft_swap(t_variable *a, t_variable *b)
{
	t_variable	*tmp;

	tmp = a;
	a = b;
	b = tmp;
}

/*
	Bubble sort : sort export linked list for initialization.
*/
void	sort_alphabetically(t_variable *export)
{
	int swapped;
	t_variable *compared;
	t_variable *tmp;

	if (export == NULL)
		return ;
	swapped = 1;
	tmp = NULL;
	while (swapped)
	{
		swapped = 0;
		compared = export;

		while (compared->next != tmp)
		{
			if (ft_strcmp(compared->name, compared->next->name) > 0)
			{
				ft_swap(compared, compared->next);
				swapped = 1;
			}
			compared = compared->next;
		}
		tmp = compared;
	}
}

/*
	returns value of ENV VAR name searched
	env : first node of our linked list of every ENV VAR
	substr : name of the variable whose value we want.
*/
char	*ft_get_env(t_variable *env, char *substr)
{
	if (!env || !substr)
		return (NULL);
	if (!ft_strcmp(substr, "?")) //gestion de errno
		return (ft_itoa(g_errno));
	while (env)
	{
		if (!ft_strcmp(env->name, substr))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
