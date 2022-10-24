/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:15 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 17:35:48 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	run the builtin
*/
int	run_builtin(const char *str, int len, t_cmdli *cmdli, t_shell *shell)
{
	if (ft_strncmp(str, "env", len) == 0)
		ft_env(shell);
	if (ft_strncmp(str, "export", len) == 0)
		ft_export(shell);
	if (ft_strncmp(str, "pwd", len) == 0)
		ft_pwd();

	return (1);
}

/*
	run the builtin function if the command input matches with our builtin list
*/
int	is_builtin(t_cmdli *cmdli, t_shell *shell)
{
	const char	*builtins[]
		= {"echo", "cd", "pwd", "env", "export", "unset", "exit", NULL};
	int			builtin_len;
	int			i;

	if (!cmdli->cmd)
		return (0);
	i = -1;
	while (builtins[++i])
	{
		builtin_len = ft_strlen(builtins[i]);
		if (ft_strncmp(builtins[i], cmdli->cmd, builtin_len) == 0)
			run_builtin(builtins[i], builtin_len, cmdli, shell);
	}
	return (0);
}


