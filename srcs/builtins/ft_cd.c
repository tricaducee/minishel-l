/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:09:31 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/14 00:43:28 by lgenevey         ###   ########.fr       */
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
	node = (t_variable *)malloc(sizeof(t_variable));
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
	getcwd : Change the current working directory
	chdir : returns 0 if success
	returns 0 = success
	Must update OLDPWD variable at first use of cd
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
		new_path = ft_strdup(cmdli->cmd_args[1]);
	if (!chdir(new_path))
		update_node("PWD", new_path);
	else
		ft_printfd(2, "cd: %s: %s\n", strerror(errno), cmdli->cmd_args[1]);
	free(new_path);
	return (1);
}
