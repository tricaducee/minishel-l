/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmdli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:40:06 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/01 11:31:17 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

t_cmdli	*error_cmdli_nl(t_cmdli **cmds_list)
{
	free_cmdli(cmds_list);
	ft_printfd(2, "#+wminishell#0: #/rsyntax error near unexpected token `#0newline#/r'#0\n");
	g_errno = 258;
	return (NULL);
}

void	error_cmdli(t_cmdli **cmds_list, char *s)
{
	free_cmdli(cmds_list);
	g_errno = 1;
	ft_printfd(2, "#+wminishell#0: #/r%s#0\n", s);
}

void	error_cmdli_interpret(t_cmdli **cmds_list, char *s)
{
	free_cmdli(cmds_list);
	ft_printfd(2, "#+wminishell#0: #/rsyntax error near unexpected token `#0%.2s#/r'#0\n", s);
	g_errno = 258;
	free(s);
}
