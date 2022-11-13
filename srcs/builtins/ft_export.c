/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/13 22:41:02 by hrolle           ###   ########.fr       */
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
	if (cmp_ret > 0)
	{
		if (prev)
			prev->next = new;
		else
			(*export) = new;
		new->next = current;
		return (0);
	}
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
/*
	no  '='	: value is null
	yes '='	: value is empty string
*/
// int	put_node(t_variable **export, t_variable *current,
// 			t_variable *prev, t_variable *new)
// {
// 	int	cmp_ret;

// 	cmp_ret = ft_strcmp(current->name, new->name);
// 	if (cmp_ret > 0)
// 	{
// 		if (prev)
// 			prev->next = new;
// 		else
// 			(*export) = new;
// 		new->next = current;
// 		return (0);
// 	}
// 	if (!cmp_ret && !current->value)
// 	{
// 		if (prev)
// 			prev->next = new;
// 		else
// 			(*export) = new;
// 		new->next = current->next;
// 		free(current->name);
// 		free(current);
// 		return (0);
// 	}
// 	if (!cmp_ret)
// 	{
// 		if (!new->value)
// 			return (0);
// 		if (current->value)
// 			free(current->value);
// 		current->value = new->value;
// 		return (0);
// 	}
// 	return (1);
// }

/*
	parcourir export, si variable deja existante alors la remplacer
	autrement ajouter le nouveau noeud au bon endroit selon le tri insertion
*/
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

/*
	parcourir env, si variable deja existante alors la remplacer
	autrement ajouter le nouveau noeud a la fin
*/

void	replace_node_env(t_variable *env, t_variable *new)
{
	t_variable	*prev;

	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, new->name))
		{
			env->value = new->value;
			free(new->name);
			free(new);
			return ;
		}
		prev = env;
		env = env->next;
	}
	prev->next = malloc(sizeof(t_variable));
	if (prev->next)
	{
		prev->next->name = new->name;
		prev->next->value = new->value;
	}
}

/*
	Creer nouveau noeud avec valeurs des arguments
*/

int	export_inset(char *s)
{
	if (!s)
		return (0);
	if (*s >= '0' && *s <= '9')
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
			if (!export_inset(new->name))
			{
				free(new->name);
				free(new->value);
				free(new);
				ft_printfd(2,
					"#+wminishell#0: export: `%s': #/r%s#0\n",
					cmdli->cmd_args[i - 1], "not a valid identifier");
				g_errno = 1;
			}
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