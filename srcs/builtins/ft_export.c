/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/30 16:46:47 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	print la liste chainee stockee dans la struc shell.export
	print est different si on n'a pas de valeur (premier OLDPWD par exemple)
*/
static void	print_export(t_variable *top)
{
	t_variable	*top_copy;

	if (top == NULL)
		return ;
	top_copy = top;
	while (top_copy)
	{
		if (top_copy->value)
			printf("declare -x %s=\"%s\"\n", top_copy->name, top_copy->value);
		else
			printf("declare -x %s\n", top_copy->name);
		top_copy = top_copy->next;
	}
}

/*
	without args : just print export

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
int	ft_export(t_shell *shell, t_cmdli *cmdli)
{
	t_variable	*node;
	int			invalid_identifier;

	if (!cmdli->cmd_args)
	{
		print_export(shell->export);
		return (1);
	}
	node = shell->export;
	invalid_identifier = 0;
	while (*cmdli->cmd_args)
	{
		if (!ft_strcmp(*cmdli->cmd_args, "="))
		{
			invalid_identifier = 1;
			continue ;
		}
		while (node)
		{
			if (!ft_strcmp(*cmdli->cmd_args, node->name))
				printf("Ca match !\n");
			node = node->next;
		}
		++cmdli->cmd_args;
	}
	return (1);
}
