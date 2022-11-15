/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:15 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/15 00:18:47 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

void	no_cmd(t_cmdli *cmdli)
{
	if (cmdli->file_in)
		set_file_in(cmdli);
	if (cmdli->file_out)
		set_file_out(cmdli);
	if (cmdli->pipe_in)
		close_pipe(cmdli->pipe_in);
}

/*
	run the builtin
*/
int	is_builtin(t_cmdli **cmdli, char *read)
{
	if (!(*cmdli)->cmd)
		no_cmd(*cmdli);
	else if (ft_strcmp((*cmdli)->cmd, "env") == 0)
		ft_env();
	else if (ft_strcmp((*cmdli)->cmd, "export") == 0)
		ft_export((*cmdli));
	else if (ft_strcmp((*cmdli)->cmd, "unset") == 0)
		ft_unset((*cmdli)->cmd_args);
	else if (ft_strcmp((*cmdli)->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp((*cmdli)->cmd, "echo") == 0)
		ft_echo(&(*cmdli)->cmd_args[1]);
	else if (ft_strcmp((*cmdli)->cmd, "cd") == 0)
		ft_cd((*cmdli));
	else if (ft_strcmp((*cmdli)->cmd, "exit") == 0)
		ft_exit(cmdli, read, 1);
	else
		return (0);
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
// int	is_builtin(t_cmdli *cmd)
// {
// 	const char	*builtins[]
// 		= {"echo", "cd", "pwd", "env", "export", "unset", "exit", NULL};
// 	int			i;

// 	if (!cmd || !cmd->cmd)
// 		return (0);
// 	i = 0;
// 	while (builtins[i])
// 	{
// 		if (ft_strcmp(builtins[i], cmd->cmd) == 0)
// 			return (run_builtin(builtins[i], cmd));
// 		++i;
// 	}
// 	return (0);
// }
