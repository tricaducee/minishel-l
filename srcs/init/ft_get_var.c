/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 04:32:21 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 04:38:38 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_get_var(char *substr)
{
	t_shell		*shell;
	t_variable	*env;

	shell = ft_get_shell(NULL);
	env = shell->env;
	if (!env || !substr)
		return (NULL);
	if (!ft_strcmp(substr, "?"))
		return (ft_itoa(g_errno));
	while (env)
	{
		if (!ft_strcmp(env->name, substr))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
