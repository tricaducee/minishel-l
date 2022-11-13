/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/13 23:45:15 by lgenevey         ###   ########.fr       */
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

int	cmp_ret_is_greater(t_variable **export, t_variable *prev,
						t_variable *current, t_variable *new)
{
	if (prev)
		prev->next = new;
	else
		(*export) = new;
	new->next = current;
	return (1);
}

int	cmp_ret_is_equal(t_variable *new, t_variable *current)
{
	if (!new->value)
		return (0);
	if (current->value)
		free(current->value);
	current->value = new->value;
	return (0);
}

int	put_node(t_variable **export, t_variable *current,
			t_variable *prev, t_variable *new)
{
	int	cmp_ret;

	cmp_ret = ft_strcmp(current->name, new->name);
	if (cmp_ret_is_greater(export, prev, new, current))
		return (0);
	if (!cmp_ret && !current->value)
	{
		if (prev)
			prev->next = new;
		else
			(*export) = new;
		new->next = current->next;
		free(current->name);
		free(current);
		return (0);
	}
	if (!cmp_ret_is_equal(new, current))
		return (0);
	return (1);
}

/*
	Creer nouveau noeud avec valeurs des arguments
*/

int	export_inset(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != '_' && (*s < 'a' || *s > 'z')
			&& (*s < 'A' || *s > 'Z')
			&& (*s < '0' || *s > '9'))
			return (0);
			s++;
	}
	return (1);
}

void	free_content_node_and_print(t_cmdli *cmdli, t_variable *new, int *i)
{
	free(new->name);
	free(new->value);
	free(new);
	ft_printfd(2, "#+wminishell#0: export: `%s': #/r%s#0\n",
		cmdli->cmd_args[*i - 1], "not a valid identifier");
	g_errno = 1;
}

void	ft_export(t_cmdli *cmdli)
{
	t_shell			*shell;
	t_variable		*new;
	int	i;

	shell = ft_get_shell(NULL);
	new = NULL;
	if (cmdli->cmd_args[1])
	{
		i = 1;
		while (cmdli->cmd_args[i])
		{
			new = create_var_node(cmdli->cmd_args[i++]);
			if (!export_inset(new->name)
				|| (new->name[0] >= '0' && new->name[0] <= '9'))
				free_content_node_and_print(cmdli, new, &i);
			else
			{
				replace_node(&shell->export, new);
				if (new->value)
					replace_node_env(shell->env, new);
			}
		}
	}
	else
		print_export();
}

// free dans export si value = NULL
// free dans env si la variable existe