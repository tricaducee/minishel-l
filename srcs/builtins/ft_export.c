/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/07 01:52:24 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	print la liste chainee stockee dans la struc shell.export
	print est different si on n'a pas de valeur (premier OLDPWD par exemple)
*/
static void	print_export(void)
{
	t_variable	*export;

	export = ft_get_export();
	if (export == NULL)
		return ;
	while (export)
	{
		if (export->value)
			printf("declare -x %s=\"%s\"\n", export->name, export->value);
		else
			printf("declare -x %s\n", export->name);
		export = export->next;
	}
}

t_variable	*get_last_node(t_variable *list)
{
	t_variable	*last;

	if (!list)
		return (NULL);
	last = list;
	while (list)
	{
		last = list;
		list = list->next;
	}
	return (last);
}

void	add_node_back(t_variable **list, t_variable *new)
{
	t_variable	*last;

	if (*list && new)
	{
		last = get_last_node(*list);
		last->next = new;
	}
	else
		*list = new;
}

/*
	a faire : is_not_valid_identifier, avec tableau const des char non autorises et boucler dessus
	a faire : pourquoi continue ne marche pas
	a faire : raccourcir cette fonction de mort
*/
int	ft_export(t_cmdli *cmdli)
{
	t_variable	*export;
	int			invalid_identifier;
	char		**cmd_args_split;
	int			i;

	if (ft_strslen(cmdli->cmd_args) == 1)
	{
		print_export();
		return (1);
	}
	invalid_identifier = 0;
	i = 1;
	while (cmdli->cmd_args[i])
	{
		if (!ft_strcmp(cmdli->cmd_args[i], "=") || !ft_strcmp(cmdli->cmd_args[i], "-"))
			invalid_identifier = 1;
			//continue ;
		cmd_args_split = ft_split(cmdli->cmd_args[i], '=');
		export = ft_get_export(); // revenir au debut de la liste
		while (export)
		{
			if (ft_strcmp(cmd_args_split[0], export->name) == 0)
			{
				if (!ft_strchr(cmdli->cmd_args[i], '='))
				{
					printf("pas de = : [%s]\n", cmdli->cmd_args[i]);
					free(export->value);
					export->value = NULL;
					break ;
				}
				else if (cmd_args_split[1] == NULL)
				{
					printf("PATH= : [%s]\n", cmdli->cmd_args[i]);
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
			if (!export) // parcouru toute la liste sans trouver equivalent => ajouter nouveau noeud
			{
				printf("nouveau : [%s]\n", cmdli->cmd_args[i]);
				export = ft_get_export(); // revenir au debut de la liste
				insert_new_node(&export, create_t_variable_node(cmdli->cmd_args[i]));
			}
		}
		free(cmd_args_split);
		++i;
	}
	if (invalid_identifier)
		ft_printfd(2, "export: `=': not a valid identifier\n");
	return (1);
}

/*
	[OK] without args : just print export

	variable nouvelle :

	minuscule et majuscules meme fonctionnement
	env bonjour=salut
	export bonjour="salut"

	nom
	env		rien faire
	export	declare -x nom

	prenom=
	env		prenom=
	export	declare -x prenom=""

	logname
	env		rien a faire
	export	declare -x logname

	ignorer si l'argument commence par _

	variable existante
	pour ecraser une variable existante, doit etre en majuscule.
	pas besoinde verifier si l'argument est en majuscule, on va comparer si
	c'est strictement identique aux noms des variables d'environnment.

	LOGNAME
	env		ne rien faire
	export	ne rien faire

	LOGNAME=
	env		vider la valeur -- LOGNAME=
	export	vider la valeur -- declare -x LOGNAME=""

	si l'argument est '='
	erreur : export: `=': not a valid identifier mais execute quand meme les
	changements

*/

//creer un nouveau noeud et y assigner les nouvelles valeurs
// si '=' trouvé alors aussi dans env a la fin

//fonction qui met a jour la variable,
// dans env et export, avec les nouvelles valeurs
//void	update_value(t_variable *env, t_variable *export, char *arg)
// il faudra les split !

// print export dans un fichier, write dans un fd, utiliser printfd pour ecrire dans le fd si yen a un sinon dans stdin 1
// set_file_out (set_redirections dans dossier execution)