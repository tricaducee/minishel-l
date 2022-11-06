/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:31 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/06 20:13:48 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	Change Directory
	Must update pwd env variable
*/
int	ft_cd(t_cmdli *cmdli)
{
	char	*path;

	path = NULL;
	if (!cmdli->cmd_args[1])
	{
		path = ft_get_var("HOME");
		chdir(path);
	}
	else if (chdir(cmdli->cmd_args[1]))
		ft_printfd(2, "cd: %s: %s\n", strerror(errno), cmdli->cmd_args[1]);
	free(path);
	return (1);
}

// free le retour de get var
// si pipe faire fork sinon pas. mais pas dans env et export
