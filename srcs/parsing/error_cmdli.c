/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmdli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:40:06 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 06:41:36 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmdli	*error_cmdli_nl(t_cmdli **cmds_list)
{
	free_cmdli(cmds_list);
	printf("minishell: syntax error near unexpected token `newline'\n");
	g_errno = 258;
	return (NULL);
}

void	error_cmdli(t_cmdli **cmds_list, char *s)
{
	free_cmdli(cmds_list);
	g_errno = 1;
	printf("%s\n", s);
}

void	error_cmdli_interpret(t_cmdli **cmds_list, char *s)
{
	free_cmdli(cmds_list);
	printf("minishell: syntax error near unexpected token `%.2s'\n", s);
	g_errno = 258;
	free(s);
}
