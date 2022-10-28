/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/28 08:31:39 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Creates a copy of env linked list in an other linked list
	returns a t_list export not sorted
*/
t_list	*init_export(t_list *env)
{
	t_list	*export;
	t_list	*env_cpy;

	if (!env)
		return (NULL);
	export = NULL;
	env_cpy = env;
	while (env_cpy)
	{
		ft_lstadd_back(&export, ft_lstnew(env_cpy->content));
		env_cpy = env_cpy->next;
	}
	sort_alphabetically(export);
	return (export);
}


// free les strings des noeuds depuis export ca va aussi le faire pour env
// car il y aura plus de noeud ici

// par contre free les noeuds des deux cotes