/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/28 06:17:40 by lgenevey         ###   ########.fr       */
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
	bool	is_oldpwd;

	if (!env)
		return (NULL);
	export = NULL;
	env_cpy = env;
	is_oldpwd = 0;
	while (env_cpy)
	{
		if (export == NULL)
			export = ft_lstnew(env_cpy->content);
		if (ft_strncmp("OLDPWD", env_cpy->content, 6) != 0)
		{
			//printf("init_export env_cpy->content: [%s]\n", env_cpy->content);
			is_oldpwd = 1;
		}
		ft_lstadd_back(&export, ft_lstnew(env_cpy->content));
		env_cpy = env_cpy->next;
	}
	if (is_oldpwd)
		ft_lstadd_back(&export, ft_lstnew("OLDPWD"));
	sort_alphabetically(export);
	return (export);
}


// free les strings des noeuds depuis export ca va aussi le faire pour env
// car il y aura plus de noeud ici

// par contre free les noeuds des deux cotes