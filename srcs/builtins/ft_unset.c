/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:33:42 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/25 20:53:06 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	It takes one ore more arguments, UPPERCASE letters only, with OR without $
	If exists : replace the env value with blank string and newline (in env and export list)
	(does not delete the node because echo should be able to find the variable
	and print blank line)

	Example :
	bash-3.2$ unset PWD
	bash-3.2$ echo $PWD

	bash-3.2$

	if env is empty or unset has no argument we return nothing
	else returns the new updated list if variable name exists.
*/
void	ft_unset(t_shell *shell, char **args)
{
	int		i;
	t_list	*env;
	//t_list	*export;
	size_t	name_size;

	if (!shell->env || !shell->export || !args)
		return ;
	i = 0;
	while (args[i])
	{
		if (!ft_is_uppercase(args[i]))
			return ;
		env = shell->env;
		name_size = ft_strlen(args[i]); //taille du nom de la variable
		while (env)
		{
			if (ft_strncmp(args[i], env->content, name_size) == 0)
			{
				printf("ft_unset argument %d : [%s]\n", i, args[i]);
				
				env->next = env->next->next;
				break ;
			}
			env = env->next;
		}
		++i;
	}
}
