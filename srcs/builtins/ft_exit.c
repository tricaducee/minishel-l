/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:25:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/13 23:01:12 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

int	check_exit_code(char **args)
{
	unsigned int	i;

	if (!args || !args[1])
		return (g_errno);
	i = 0;
	if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1])
		i++;
	while (args[1][i] && (args[1][i] >= '0' && args[1][i] <= '9'))
		i++;
	if (args[1][i])
	{
		ft_printfd(2,
			"#+wminishell#0: exit: %s: #/rnumeric argument required#0\n",
			args[1]);
		return (255);
	}
	return (ft_atoi(args[1]));
}

void	ft_exit(t_cmdli **cmdli, char *read, int mode)
{
	t_shell	*shell;
	int		code;

	if (mode)
	{
		code = check_exit_code((*cmdli)->cmd_args);
		if (code != 255 && (*cmdli)->cmd_args && (*cmdli)->cmd_args[1]
			&& (*cmdli)->cmd_args[2])
		{
			ft_printfd(2, "#+wminishell#0: exit: #/rtoo many arguments#0\n");
			g_errno = 1;
			return ;
		}
	}
	else
		code = 0;
	shell = ft_get_shell(NULL);
	if (shell)
	{
		if (shell->export)
			free_nodes_contents(&shell->export);
		if (shell->env)
			free_nodes(&shell->env);
	}
	free_cmdli(cmdli);
	if (read)
		free(read);
	clear_history();
	ft_printfd(1, "Good Bye ! See you soon ;)\n");
	exit(code);
}
