/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:15 by lgenevey          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/25 21:39:18 by lgenevey         ###   ########.fr       */
=======
/*   Updated: 2022/10/27 01:12:55 by hermesrolle      ###   ########.fr       */
>>>>>>> 03806329541c7c2babf228540bd8a24f6f5b5e53
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	run the builtin
*/
<<<<<<< HEAD
int	run_builtin(const char *str, t_cmdli *cmdli, t_shell *shell, int len)
=======
int	run_builtin(const char *str, int len, t_cmdli *cmd, t_shell *shell)
>>>>>>> 03806329541c7c2babf228540bd8a24f6f5b5e53
{
	if (ft_strncmp(str, "env", len) == 0)
		ft_env(shell);
	else if (ft_strncmp(str, "export", len) == 0)
		ft_export(shell);
	else if (ft_strncmp(str, "pwd", len) == 0)
		ft_pwd();
<<<<<<< HEAD
	else if (ft_strncmp(str, "unset", len) == 0)
		ft_unset(shell, cmdli->cmd_args);
=======
	if (!ft_strncmp(str, "echo", len))
		ft_echo(cmd->cmd_args);

>>>>>>> 03806329541c7c2babf228540bd8a24f6f5b5e53
	return (1);
}

/*
	check if cmd->cmd is a builtin
	returns 0 if cmd->cmd is empty or if it's not a builtin
	if cmd->cmd matches with builtin : run the builtin
*/
<<<<<<< HEAD
int	is_builtin(t_cmdli *cmdli, t_shell *shell)
=======
int	is_builtin(t_cmdli *cmd, t_shell *shell)
>>>>>>> 03806329541c7c2babf228540bd8a24f6f5b5e53
{
	const char	*builtins[]
		= {"echo", "cd", "pwd", "env", "export", "unset", "exit", NULL};
	int			builtin_len;
	int			i;

<<<<<<< HEAD
	if (!cmdli->cmd)
=======
	if (!cmd->cmd)
>>>>>>> 03806329541c7c2babf228540bd8a24f6f5b5e53
		return (0);
	i = 0;
	while (builtins[i])
	{
		builtin_len = ft_strlen(builtins[i]);
<<<<<<< HEAD
		if (ft_strncmp(builtins[i], cmdli->cmd, builtin_len) == 0)
			run_builtin(builtins[i], cmdli, shell, builtin_len);
=======
		if (ft_strncmp(builtins[i], cmd->cmd, builtin_len) == 0)
			return (run_builtin(builtins[i], builtin_len, cmd, shell));// j'ai modifier ça, j'ai juste return le retour de la fonction pour ne pas le perdre (ça me mettais toujours "c'est pas un built-in alors que si! voilà!")
>>>>>>> 03806329541c7c2babf228540bd8a24f6f5b5e53
		++i;
	}
	return (0);
}


