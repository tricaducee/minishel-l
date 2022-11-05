/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:31:19 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/11/05 07:18:17 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	interpret(t_cmdli **cmds_list, char **cmdline,
					t_type *type, unsigned int *i)
{
	while ((*cmdline)[*i] && ((*cmdline)[*i] == ' ' ||
			((*cmdline)[*i] >= '\t' && (*cmdline)[*i] <= '\r')))
		++*i;
	if (!(*cmdline)[*i])
		return ;
	else if ((*cmdline)[*i] == '<')
		type_and_set(split_cmd(cmdline, i, '<'), cmds_list, type, 1);
	else if ((*cmdline)[*i] == '>')
		type_and_set(split_cmd(cmdline, i, '>'), cmds_list, type, 1);
	else if ((*cmdline)[*i] == '|')
		type_and_set(split_cmd(cmdline, i, '|'), cmds_list, type, 1);
	else if ((*cmdline)[*i] == '&')
		type_and_set(split_cmd(cmdline, i, '&'), cmds_list, type, 1);
	else
		type_and_set(split_cmd_sp(cmdline, i), cmds_list, type, 0);
}

t_cmdli	*get_cmds(char **cmdline)
{
	unsigned int	i;
	t_cmdli			*cmds_list;
	t_type			type;

	if (!(*cmdline))
		return (NULL);
	i = 0;
	type = 0;
	cmds_list = NULL;
	while ((*cmdline)[i])
	{
		interpret(&cmds_list, cmdline, &type, &i);
		if (!cmds_list)
			return (NULL);
	}
	if (type != CMD && type != ARG && type != RFILE && type != EMPTY)
		return (error_cmdli_nl(&cmds_list));
	return (cmdli_first(cmds_list));
}

// t_cmdli	*get_cmds(char *(*cmdline))
// {
// 	unsigned int	i;
// 	t_cmdli			*cmds_list;
// 	char			**cmds_tab;
// 	char			**tmp;

// 	if (!(*cmdline))
// 		return (NULL);
// 	i = 0;
// 	cmds_list = NULL;
// 	cmds_tab = NULL;
// 	while ((*cmdline)[i])
// 	{
// 		while ((*cmdline)[i] == ' ') //all white space
// 			++i;
// 		tmp = cmds_tab;
// 		if ((*cmdline)[i] == '<')
// 			type_and_set(split_cmd((*cmdline), &i, '<'), cmds_tab);
// 		else if ((*cmdline)[i] == '>')
// 			type_and_set(split_cmd((*cmdline), &i, '>'), cmds_tab);
// 		else if ((*cmdline)[i] == '|')
// 			type_and_set(split_cmd((*cmdline), &i, '|'), cmds_tab);
// 		else if ((*cmdline)[i] == '&')
// 			type_and_set(split_cmd((*cmdline), &i, '&'), cmds_tab);
// 		else
// 			type_and_set(split_cmd_sp((*cmdline), &i), cmds_tab);
// 		if (tmp)
// 			free(tmp);
// 		tmp = NULL;
// 	}
// 	print_tab(cmds_tab);
// 	free_tab(cmds_tab);
// 	return (cmds_list);
// }

// int	main(int ac, char **av)
// {
// 	if (ac < 2)
// 		return (1);
// 	print_cmdli(get_cmds(av[1]));
// 	return (0);
// }

// void	get_data(char *str)
// {
// 	*ptr;

// 	if (str)
// 	{
// 		ptr = str;
// 	}
// 	return (ptr);
// }

// int	main()
// {

// 	char *str = "hello";

// 	get_data(str);

// 	/////

// 	char *ptr;

// 	ptr = get_data(NULL);

// }

// char test_value;
// int  res;

// if (test_value == 't')  // 1 or 0
// 	res = var_a;
// else
// 	res = var_b;

// res = (test_value == 't') * var_a + (test_value != 't') * var_b;

// res = test_value == 't' ? var_a : var_b;
