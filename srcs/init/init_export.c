/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:29:53 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/30 15:52:59 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	Creates a copy of env linked list in an other linked list
	Add OLDPWD alone as the real bash export does
	Returns a t_variable export sorted
*/
t_variable	*init_export(t_variable *env)
{
	t_variable	*export;
	t_variable	*ret;
	t_variable	*env_cpy;

	if (!env)
		return (NULL);
	export = (t_variable *)malloc(sizeof(t_variable));
	if (!export)
		return (NULL);
	ret = export;
	env_cpy = env;
	while (env_cpy)
	{
		export->name = env_cpy->name;
		export->value = env_cpy->value;
		env_cpy = env_cpy->next;
		export->next = 	(t_variable *)malloc(sizeof(t_variable));
		if (!export->next)
			return (NULL);
		export = export->next;
	}
	export->name = ft_strdup("OLDPWD");
	export->value = ft_strdup("");
	export->next = NULL;
	sort_alphabetically(export);
	return (ret);
}



// free les strings des noeuds depuis export ca va aussi le faire pour env
// car il est possible qu'il y ait plus de noeuds dans export

// par contre free les noeuds des deux cotes