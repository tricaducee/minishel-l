/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:33:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/04 18:38:57 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	It takes one ore more arguments, UPPERCASE letters only, with OR without $
	If exists : skip next node, replace its address with next next's one
	(in both env and export lists)
*/
int	ft_unset(char **args)
{
	int			i;
	t_variable	*env;
	t_variable	*export;

	if (!args || !args[0])
		return (0);
	i = 1;
	while (args[i])
	{
		env = ft_get_env();
		export = ft_get_export();
		while (export && export->next && (ft_strcmp(args[i], export->next->name) != 0))
		{
			// avancer jusqu'au noeud qui precede la comparaison exacte
			printf("current export.name : [%s]\n", export->name);
			export = export->next;
		}
		if (export) // si on n'est pas arrive au bout
		{
			export->next = export->next->next;
			free_nodes(&export->next);
		}
		// while (env)
		// {
		// 	if (ft_strcmp(args[i], env->name) == 0)
		// 	{
		// 		printf("env.name : [%s]\n", export->name);
		// 		env->next = env->next->next;
		// 	}
		// 	env = env->next;
		// 	//free_nodes_contents(&tmp);
		// 	//free_nodes(&env);
		// }
		++i;
	}
	return (1);
}

/*
	Parcourir le char **
	Si nom strictement identique a une variable alors le skip
	faire une fonction qui skip un noeud, prend en entree un t_variable *node

*/