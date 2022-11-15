/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmdli.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 06:48:33 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/15 06:02:38 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmdli	*create_cmdli(void)
{
	t_cmdli	*ret;

	ret = malloc(1 * sizeof(t_cmdli));
	if (!ret)
		return (NULL);
	*ret = (t_cmdli){};
	ret->cmd = NULL;
	ret->cmd_args = NULL;
	ret->pipe_in = NULL;
	ret->pipe_out = NULL;
	ret->file_in = NULL;
	ret->file_out = NULL;
	ret->here_doc = NULL;
	ret->and_or = 0;
	ret->previous = NULL;
	ret->next = NULL;
	return (ret);
}

	// ret->cmd = NULL;
	// ret->cmd_args = NULL;
	// ret->pipe_in = NULL;
	// ret->pipe_out = NULL;
	// ret->file_in = NULL;
	// ret->file_out = NULL;
	// ret->file_type = EMPTY;
	// ret->here_doc = NULL;
	// ret->and_or = 0;
	// ret->previous = NULL;
	// ret->next = NULL;
