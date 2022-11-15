/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:31 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/15 05:43:12 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	creates new node with name and value mallocated
	replace node in export
	if new node has value, replace node in env
*/
void	update_node(char *name, char *value)
{
	t_shell		*shell;
	t_variable	*node;

	shell = ft_get_shell(NULL);
	node = malloc(sizeof(t_variable));
	if (!node)
		return ;
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	node->next = NULL;
	replace_node(&shell->export, node);
	if (node->value)
		replace_node_env(shell->env, node);
}

/*
	getcwd : Get the current working directory
	chdir : change current dir, returns 0 if success
	Must update OLDPWD variable at first use of cd
	Must update PWD variable after chdir
*/
int	ft_cd(t_cmdli *cmdli)
{
	char	*new_path;
	char	*actual_path;
	char	buff[PATH_MAX];

	actual_path = getcwd(buff, PATH_MAX);
	update_node("OLDPWD", actual_path);
	new_path = NULL;
	if (!cmdli->cmd_args[1])
		new_path = ft_get_var("HOME");
	else if (cmdli->cmd_args[1] || !ft_strcmp(cmdli->cmd_args[1], "."))
		new_path = cmdli->cmd_args[1];
	if (!chdir(new_path))
	{
		new_path = getcwd(buff, PATH_MAX);
		update_node("PWD", new_path);
	}
	else
		ft_printfd(2, "cd: %s: %s\n", strerror(errno), cmdli->cmd_args[1]);
	return (1);
}
