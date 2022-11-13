/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:31 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/12 23:25:27 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	update OLDPWD value in env and export
*/
void	update_oldpwd_value(char *str)
{
	t_shell	*shell;

	shell = ft_get_shell(NULL);
	while (shell->export)
	{
		if (!ft_strcmp(str, shell->export->name))
		{
			free(shell->export->value);
			shell->export->value = ft_strdup(str);
		}
		shell->export = shell->export->next;
	}
}

/*
	getcwd : Change the current working directory
	returns 0 = success
	Must update OLDPWD variable at first use of cd
*/
int	ft_cd(t_cmdli *cmdli)
{
	char	*path;
	char	*oldpwd;
	char	buff[PATH_MAX];

	oldpwd = getcwd(buff, PATH_MAX);
	//update_oldpwd_value(oldpwd);
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
