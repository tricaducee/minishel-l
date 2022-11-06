/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:15 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/06 20:08:59 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	run the builtin
*/
int	run_builtin(const char *str, t_cmdli *cmd)// ATTENTION pas strncmp car exporttttttttt n'est pas valide !
{
	if (ft_strcmp(str, "env") == 0)
		ft_env();
	if (ft_strcmp(str, "export") == 0)
		ft_export(cmd);
	if (ft_strcmp(str, "unset") == 0)
		ft_unset(cmd->cmd_args);
	if (ft_strcmp(str, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(str, "echo") == 0)
		ft_echo(&cmd->cmd_args[1]);
	if (ft_strcmp(str, "cd") == 0)
		ft_cd(cmd);
	return (1);
}
// int	run_builtin(const char *str, t_cmdli *cmd, t_shell *shell, int len)
// {
// 	cmd->pid = fork();
// 	if (cmd->pid == -1)
// 	{
// 		g_errno = errno;
// 		ft_printfd(2, "#+wminishell#0:#/r %s#0\n", strerror(g_errno));
// 		return (g_errno);
// 	}
// 	else if (!cmd->pid)
// 	{
// 		set_redirection(cmd);
// 		if (ft_strncmp(str, "env", len) == 0)
// 			ft_env(shell);
// 		else if (ft_strncmp(str, "export", len) == 0)
// 			ft_export(shell, cmd);
// 		else if (ft_strncmp(str, "pwd", len) == 0)
// 			ft_pwd();
// 		if (!ft_strncmp(str, "echo", len))
// 			ft_echo(&cmd->cmd_args[1]);
// 		if (!ft_strncmp(str, "cd", len))
// 			ft_cd(cmd->cmd_args);
// 		exit(0);
// 	}
// 	else
// 		return (close_pipe(cmd->pipe_in) + 1);
// 	return (1);
// }

/*
	check if cmd->cmd is a builtin
	returns 0 if cmd->cmd is empty or if it's not a builtin
	if cmd->cmd matches with builtin : run the builtin
*/
int	is_builtin(t_cmdli *cmd)
{
	const char	*builtins[]
		= {"echo", "cd", "pwd", "env", "export", "unset", "exit", NULL};
	int			i;

	if (!cmd || !cmd->cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd->cmd) == 0)
			return (run_builtin(builtins[i], cmd));
		++i;
	}
	return (0);
}
