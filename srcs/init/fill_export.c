/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 17:25:40 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Creates a copy of env linked list in an other linked list
	returns a t_list export not sorted
*/
t_list	*fill_export(t_list *env)
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
			ft_lstnew(env_cpy->content);
		if (ft_strncmp("OLDPWD", env_cpy->content, 6) != 0)
			is_oldpwd = 1;
		ft_lstadd_back(&export, ft_lstnew(env_cpy->content));
		env_cpy = env_cpy->next;
	}
	if (is_oldpwd)
		ft_lstadd_back(&export, ft_lstnew("OLDPWD"));
	return (export);
}
