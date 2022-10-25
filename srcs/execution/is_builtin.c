/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:15 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/25 21:39:18 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	run the builtin
*/
int	run_builtin(const char *str, t_cmdli *cmdli, t_shell *shell, int len)
{
	if (ft_strncmp(str, "env", len) == 0)
		ft_env(shell);
	else if (ft_strncmp(str, "export", len) == 0)
		ft_export(shell);
	else if (ft_strncmp(str, "pwd", len) == 0)
		ft_pwd();
	else if (ft_strncmp(str, "unset", len) == 0)
		ft_unset(shell, cmdli->cmd_args);
	return (1);
}

/*
	check if cmd_name is a builtin
	returns 0 if cmd_name is empty or if it's not a builtin
	if cmd_name matches with builtin : run the builtin
*/
int	is_builtin(t_cmdli *cmdli, t_shell *shell)
{
	const char	*builtins[]
		= {"echo", "cd", "pwd", "env", "export", "unset", "exit", NULL};
	int			builtin_len;
	int			i;

	if (!cmdli->cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		builtin_len = ft_strlen(builtins[i]);
		if (ft_strncmp(builtins[i], cmdli->cmd, builtin_len) == 0)
			run_builtin(builtins[i], cmdli, shell, builtin_len);
		++i;
	}
	return (0);
}


