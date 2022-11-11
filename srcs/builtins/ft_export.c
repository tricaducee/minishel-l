/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:46:29 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/11 22:19:40 by lgenevey         ###   ########.fr       */
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

/*
	update and fill env variables depending on the following cases
		si bad premier char		:	print error et passer au pointeur suivant
		si _					:	juste passer au suivant

		[ok]connu et sans =	:	ne rien faire, ni dans env, ni dans export
		[ok mais valeur cheloue dans export]connu avec = mais vide	:	vider valeur existante		mais garder = et mettre "" pour export

		nouveau et sans =		:	rien dans env, nouveau noeud dans export
		nouveau avec = mais vide:	nouveau noeud dans export, valeur vide, trier. Nouveau noeud dans env qui pointe sur export
		nouveau avec valeur		:	nouveau noeud dans export, valeur pleine,  trier, Nouveau noeud dans env qui pointe sur export
*/
static int	run_env(t_cmdli *cmdli, t_variable *env, int *i)
{
	char	**arg;

	arg = ft_split(cmdli->cmd_args[*i], '=');
	while (env)
	{
		if (ft_strcmp(arg[0], env->name) == 0)
		{
			if (!ft_strchr(cmdli->cmd_args[*i], '='))
			{
				free(env->value);
				env->value = NULL;
				break ;
			}
			else if (arg[1] == NULL)
			{
				free(env->value);
				env->value = NULL;
				//env->value = NULL;
				break ;
			}
			else
			{
				free(env->value);
				env->value = arg[1];
				break ;
			}
		}
		env = env->next;
		if (!env)
			return (0);
	}
	free(arg);
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
	//t_variable	*env;
	int			first_time;
	int			i;

	if (ft_strslen(cmdli->cmd_args) == 1)
		return (print_export());
	first_time = 0;
	i = 0;
	while (cmdli->cmd_args[++i])
	{
		if (is_bad_arg(cmdli->cmd_args[i], &i, first_time))
			continue ;
		export = ft_get_export();
		//env = ft_get_env();
		if (!run_env(cmdli, ft_get_env(), &i))
			insert_new_node(&export, create_var_node(cmdli->cmd_args[i]));
	}
	return (1);
}

// print export dans un fichier, write dans un fd, utiliser printfd pour ecrire dans le fd si yen a un sinon dans stdin 1
// set_file_out (set_redirections dans dossier execution)