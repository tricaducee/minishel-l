/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:15 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/27 01:12:55 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	run the builtin
*/
int	run_builtin(const char *str, int len, t_cmdli *cmd, t_shell *shell)
{
	if (ft_strncmp(str, "env", len) == 0)
		ft_env(shell);
	if (ft_strncmp(str, "export", len) == 0)
		ft_export(shell);
	if (ft_strncmp(str, "pwd", len) == 0)
		ft_pwd();
	if (!ft_strncmp(str, "echo", len))
		ft_echo(cmd->cmd_args);

	return (1);
}

/*
	check if cmd->cmd is a builtin
	returns 0 if cmd->cmd is empty or if it's not a builtin
	if cmd->cmd matches with builtin : run the builtin
*/
int	is_builtin(t_cmdli *cmd, t_shell *shell)
{
	const char	*builtins[]
		= {"echo", "cd", "pwd", "env", "export", "unset", "exit", NULL};
	int			builtin_len;
	int			i;

	if (!cmd->cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		builtin_len = ft_strlen(builtins[i]);
		if (ft_strncmp(builtins[i], cmd->cmd, builtin_len) == 0)
			return (run_builtin(builtins[i], builtin_len, cmd, shell));// j'ai modifier ça, j'ai juste return le retour de la fonction pour ne pas le perdre (ça me mettais toujours "c'est pas un built-in alors que si! voilà!")
		++i;
	}
	return (0);
}


