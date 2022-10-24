/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:13:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 20:48:38 by lgenevey         ###   ########.fr       */
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
	t_list *ptr1;
	t_list *lptr;

	if (export == NULL)
		return ;
	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = export;

		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				ft_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

/*
	returns value of ENV VAR name searched
	env : first node of our linked list of every ENV VAR
	substr : name of the variable whose value we want.
*/
char	*ft_get_env(t_list *env, char *substr)
{
	t_list	*ptr;
	char	*ret;
	size_t	from;
	size_t	to;

	if (!env || !substr)
		return (NULL);
	ptr = env;
	ret = ft_strdup("");
	while (ptr)
	{
		from = (ft_strchr(ptr->content, '=') - (char *)ptr->content) + 1;
		to = ft_strlen(substr);
		if (ft_strncmp(substr, ptr->content, to) == 0)
		{
			ret = ft_substr(ptr->content, from, to - from);
			printf("ft_get_env ret: [%s]\n", ret);
		}
		ptr = ptr->next;
	}
	return (ret);
}
