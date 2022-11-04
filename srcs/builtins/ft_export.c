/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/04 18:15:09 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
	creates new node with splitted content from argument string
*/
void	update_list(t_variable **list, char *arg)
{
	t_variable	*new;

	new = create_t_variable_node(arg);
	add_node_back(list, new);
	printf("update_list\n");
	printf("new content, name :[%s] value :[%s]\n", new->name, new->value);
}

int	ft_export(t_shell *shell, t_cmdli *cmdli)
{
	t_variable	*export;
	int			invalid_identifier;

	if (ft_strslen(cmdli->cmd_args) == 1)
	{
		print_export();
		return (1);
	}
	export = shell->export; // ft_get_export et retirer argument shell
	invalid_identifier = 0;
	while (*cmdli->cmd_args)
	{
		if (!ft_strcmp(*cmdli->cmd_args, "="))
		{
			invalid_identifier = 1;
			continue ;
		}
		while (export)
		{
			if (ft_strcmp(*cmdli->cmd_args, export->name) == 0)
			{
				return (1);
			}
			export = export->next;
		}
		++cmdli->cmd_args;
	}
	if (invalid_identifier)
		printf("export: `=': not a valid identifier\n");
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