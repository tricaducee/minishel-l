/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/12 22:04:16 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	print la liste chainee stockee dans la struc shell.export
	print est different si on n'a pas de valeur (premier OLDPWD par exemple)
	pointeur null : pas les guillemets
	chaine vide : oui les guillemets
*/
static int	print_export(void)
{
	t_variable	*export;

	export = ft_get_export();
	if (export == NULL)
		return (0);
	while (export)
	{
		if (!export->value)
			printf("declare -x %s\n", export->name);
		else
			printf("declare -x %s=\"%s\"\n", export->name, export->value);
		export = export->next;
	}
	return (1);
}

// modifier oldpwd des le moment ou on appelle cd

/*
	no '=' : value is null
	yes '=' : value is empty string
*/
int	put_node(t_variable **export, t_variable *current,
			t_variable *prev, t_variable *new)
{
	int	cmp_ret;

	cmp_ret = ft_strcmp(current->name, new->name);
	if (cmp_ret > 0)
	{
		if (prev)
			prev->next = new;
		else
			(*export) = new;
		new->next = current;
		return (0);
	}
	if (!cmp_ret)
	{
		if (!new->value)
			return (0);
		if (current->value)
			free(current->value);
		current->value = new->value;
		return (0);
	}
	return (1);
}

void	replace_node(t_variable **export, t_variable *new)
{
	t_variable	*prev;
	t_variable	*current;
	static int	i;

	prev = NULL;
	current = *export;
	i++;
	while (current)
	{
		if (!put_node(export, current, prev, new))
			return ;
		prev = current;
		current = current->next;
	}
	if (!current)
		prev->next = new;
}

void	ft_export(t_cmdli *cmdli)
{
	t_shell			*shell;
	t_variable		*new;
	unsigned int	i;

	shell = ft_get_shell(NULL);
	new = NULL;
	if (cmdli->cmd_args[1])
	{
		i = 1;
		while (cmdli->cmd_args[i])
		{
			new = create_var_node(cmdli->cmd_args[i++]);
			replace_node(&shell->export, new);
			//if ()
		}
	}
	else
		print_export();
}
