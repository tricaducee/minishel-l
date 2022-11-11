/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/11 01:18:00 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	print la liste chainee stockee dans la struc shell.export
	print est different si on n'a pas de valeur (premier OLDPWD par exemple)
*/
static int	print_export()
{
	t_variable	*export;

	export = ft_get_export();
	if (export == NULL)
		return (0);
	while (export)
	{
		if (export->value)
			printf("declare -x %s=\"%s\"\n", export->name, export->value);
		else
			printf("declare -x %s\n", export->name);
		export = export->next;
	}
	return (1);
}

// DELETE IF NOT NECESSARY
// t_variable	*get_last_node(t_variable *list)
// {
// 	t_variable	*last;

// 	if (!list)
// 		return (NULL);
// 	last = list;
// 	while (list)
// 	{
// 		last = list;
// 		list = list->next;
// 	}
// 	return (last);
// }

// void	add_node_back(t_variable **list, t_variable *new)
// {
// 	t_variable	*last;

// 	if (*list && new)
// 	{
// 		last = get_last_node(*list);
// 		last->next = new;
// 	}
// 	else
// 		*list = new;
// }

/*
	return 1 if c is not a valid identifier or doesnt content any =
	writes only once the message, not for every bad char
*/
static int is_bad_arg(char *str, int *i, int first_time)
{
	if (str[0] == '_')
	{
		++(*i);
		return (1);
	}
	if (!ft_isalpha(str[0]))
	{
		if (first_time)
			ft_printfd(2, "export: `%c': not a valid identifier\n", str[0]);
		first_time = 0;
		++(*i);
		return (1);
	}
	return (0);
}


/*
	a faire : raccourcir cette fonction de mort
	a faire : aussi ajouter un noeud dans env
*/
int	ft_export(t_cmdli *cmdli)
{
	t_variable	*export;
	t_variable	*env;
	char		**cmd_args_split;
	int			first_time;
	int			i;

	if (ft_strslen(cmdli->cmd_args) == 1)
		return (print_export());
	first_time = 1;
	i = 1;
	while (cmdli->cmd_args[i])
	{
		if (is_bad_arg(cmdli->cmd_args[i][0], &i, first_time))
		{
			//first_time = 0;
			continue ;
		}
		cmd_args_split = ft_split(cmdli->cmd_args[i], '=');
		export = ft_get_export();	// revenir au debut de la liste
		env = ft_get_env();			// revenir au debut de la liste
		while (export)
		{
			if (ft_strcmp(cmd_args_split[0], export->name) == 0)
			{
				if (!ft_strchr(cmdli->cmd_args[i], '='))
				{
					free(export->value);
					export->value = NULL;
					break ;
				}
				else if (cmd_args_split[1] == NULL)
				{
					free(export->value);
					export->value = ft_strdup("");
					break ;
				}
				else
				{
					free(export->value);
					export->value = cmd_args_split[1];
					break ;
				}
			}
			export = export->next;
			if (!export)
			{
				export = ft_get_export(); // revenir au debut de la liste
				insert_new_node(&export, create_var_node(cmdli->cmd_args[i]));
			}
		}
		free(cmd_args_split);
		++i;
	}
	return (1);
}

//fonction qui met a jour la variable,
// dans env et export, avec les nouvelles valeurs
//void	update_value(t_variable *env, t_variable *export, char *arg)
// il faudra les split !

// print export dans un fichier, write dans un fd, utiliser printfd pour ecrire dans le fd si yen a un sinon dans stdin 1
// set_file_out (set_redirections dans dossier execution)