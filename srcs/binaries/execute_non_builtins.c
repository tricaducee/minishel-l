/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:22:37 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/03 03:42:16 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	cree un fork (un nouveau processus enfant)
	dans lequel on va executer la commande en argument
*/
// void	exec_cmd(char **cmd)
// {
// 	pid_t	pid;
// 	int		status;

// 	status = 0;
// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork");
// 	else if (pid > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 		kill(pid, SIGTERM);
// 	}
// 	else
// 	{
// 		if (execve(cmd[0], cmd, NULL) == -1)
// 			printf("exec_cmd zsh: command not found: %s\n", cmd[0]);
// 		exit(1);
// 	}
// }

// recuperer le nom de la commande, utile pour le retour de exit()