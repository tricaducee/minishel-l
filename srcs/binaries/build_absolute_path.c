/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:53:36 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/15 23:06:23 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
	in case there is no PATH variable in env
*/
static void	print_and_free(char *path, char *bin, char **path_split)
{
	write(1, "zsh: command not found (path cleared)\n", 39);
	free(path);
	free(bin);
	free(path_split);
}

/*
	but : voir si on nous a donne un chemin absolu vers un binaire ou pas (dans
	ce cas on remplace la commande par son emplacement absolu car execve
	necessite un chemin absolu vers les binaires a executer)
	et verifier si le binaire existe avec access().

	Recuperer le contenu de la variable PATH
	S'il est vide on le cree soit meme
	Si la s entree n'est pas un chemin absolu on le cherche
		on va split la string PATH par les :
		chercher ou est notre binaire en parcourant chaque dossier
		access va verifier l'existence du fichier
	on remplace le binaire donné (ex:ls) par son emplacmement (ex:bin/ls)
*/
void	build_absolute_path(char **str)
{
	char	*path;
	char	*bin;
	char	**path_split;
	int		i;

	path = ft_strdup(getenv("PATH"));
	bin = NULL;
	path_split = NULL;
	if (str[0] == NULL)
		return ;
	if (path == NULL)
	{
		print_and_free(path, bin, path_split);
		return ;
	}
	if (str[0][0] != '/' && ft_strncmp(str[0], "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		i = -1;
		while (path_split[++i])
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + 1 + ft_strlen(str[0]) + 1));
			if (bin == NULL)
				break ;
			ft_strcat(bin, path_split[i]);
			ft_strcat(bin, "/");
			ft_strcat(bin, str[0]);
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
		}
		ft_free_ppointer(path_split);
		free(str[0]);
		str[0] = bin;
		printf("get_absolute_path str[0] : [%s]\n", str[0]);
	}
	else
	{
		free(path);
		path = NULL;
		free(path_split);
	}
}