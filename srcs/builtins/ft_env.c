/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:12:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/13 23:00:50 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print a list from a copy pointer
*/
static void	printlist(t_variable *top)
{
	while (top)
	{
		printf("%s=%s\n", top->name, top->value);
		top = top->next;
	}
}

/*
	Displays env variables
	The order we see is when items are created
*/
int	ft_env(void)
{
	t_variable	*env;

	env = ft_get_env();
	printlist(env);
	return (1);
}
