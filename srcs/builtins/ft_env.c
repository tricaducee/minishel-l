/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:12:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/31 20:28:57 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print a list from a copy pointer
*/
static void	printlist(t_variable *top)
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
	Displays env variables
	The order we see is when items are created
*/
int	ft_env(t_shell *shell)
{
	printlist(shell->env);
	return (1);
}
