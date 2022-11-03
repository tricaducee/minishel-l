/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:31 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 01:37:29 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	Change Directory
	Must update pwd env variable
*/
int	ft_cd(char **opti)
{
	char	*directory;

	directory = NULL;
	if (!opti[1])
		directory = ft_get_var("HOME");
	else if (chdir(opti[1]) != 0)
		ft_printfd(2, "cd: %s: %s\n", strerror(errno), opti[0]);
	return (1);
}
