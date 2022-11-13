/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/12 17:16:06 by lgenevey         ###   ########.fr       */
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
		if (!export->value) // "" != NULL -- chaine non nulle
			printf("declare -x %s\n", export->name);
		else
			printf("declare -x %s=\"%s\"\n", export->name, export->value);
		export = export->next;
	}
	return (1);
}


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
		{
			ft_printfd(2, "export: `%s': not a valid identifier\n", str);
			first_time = 0;
		}
		++(*i);
		return (1);
		printf("coucou\n");
	}
	return (0);
}

/*
	update and fill env variables depending on the following cases
		si bad premier char		:	print error et passer au pointeur suivant
		si _ uniquement			:	juste passer au suivant

		[ok]connu et sans =	:	ne rien faire, ni dans env, ni dans export
		[]connu avec = mais vide	:	vider valeur existante		mais garder = et mettre "" pour export

		nouveau et sans =		:	rien dans env, nouveau noeud dans export
		nouveau avec = mais vide:	nouveau noeud dans export, valeur vide, trier. Nouveau noeud dans env qui pointe sur export
		nouveau avec valeur		:	nouveau noeud dans export, valeur pleine,  trier, Nouveau noeud dans env qui pointe sur export

		premier = separe le nom de la valeur, jamais de = dans le nom

*/

/*
	Mets a jour la valeur d'un noeud d'export selon env
	Parcours la liste export, s'arreter au bon emplacement par rapport a env
	et faire pointer la value de export sur la value de env
*/
void	find_and_replace(char *name, char *value)
{
	t_variable	*export;

	export = ft_get_export();
	while (export)
	{
		if (ft_strcmp(export->name, name))
		{
			if (!export->value)
				export->value = value;
			else
			{
				free(export->value);
				export->value = value;
			}
			printf("export.value : [%s]\n", export->value);
			return ;
		}
		export = export->next;
	}

}
static int	variable_exists(t_cmdli *cmdli, t_variable *env, int *i)
{
	char	**arg;

	arg = ft_split(cmdli->cmd_args[*i], '=');
	while (env)
	{
		if (ft_strcmp(arg[0], env->name) == 0)
		{
			if (arg[1] != NULL) // si on a une valeur, remplacer l'actuelle
			{
				printf("nom=valeur\n");
				printf("env.value avant free : [%s]\n", env->value);
				free(env->value);
				env->value = arg[1]; //already malloced with split
				printf("env.value apres free : [%s]\n", env->value);
				find_and_replace(env->name, arg[1]); // attribuer la valeur a export aussi
				break ;
			}
			else if (!arg[1]) // si on a un = mais que la valeur est nulle
			{
				printf("nom=\n");
				free(env->value);
				env->value = NULL;
				find_and_replace(env->name, env->value);
				break ;
			}
		}
		env = env->next;
		if (!env)
			return (0);
	}
	free(arg);
	free(arg[0]);
	return (1);
}

/*
	a faire : raccourcir cette fonction de mort
	a faire : aussi ajouter un noeud dans env
*/
int	ft_export(t_cmdli *cmdli)
{
	t_variable	*export;
	t_variable	*env;
	int			first_time;
	int			i;

	if (!cmdli->cmd_args[1])
		return (print_export());
	first_time = 1;
	i = 0;
	while (cmdli->cmd_args[++i])
	{
		if (is_bad_arg(cmdli->cmd_args[i], &i, first_time))
			continue ;
		env = ft_get_env();
		export = ft_get_export();
		if (!variable_exists(cmdli, env, &i))
		{
			if (ft_strchr(cmdli->cmd_args[i], '='))
				add_node_back(&env, create_var_node(cmdli->cmd_args[i]));
			insert_new_node(&export, create_var_node(cmdli->cmd_args[i]));
		}
	}
	return (1);
}

// print export dans un fichier, write dans un fd, utiliser printfd pour ecrire dans le fd si yen a un sinon dans stdin 1
// set_file_out (set_redirections dans dossier execution)