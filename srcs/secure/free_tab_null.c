/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab_null.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:30:14 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/03 04:42:43 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**free_tab_null(char **ss)
{
	unsigned int	i;

	i = 0;
	if (!ss)
		return (NULL);
	while (ss[i])
		free(ss[i++]);
	free(ss);
	return (NULL);
}
