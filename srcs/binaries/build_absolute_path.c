/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:53:36 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/21 16:33:10 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	clean(char **path_split, char **args)
{
	ft_free_ppointer(path_split);
	free(args[0]);
}

/*
	if command is not given as an absolute path, we replace it by absolute path

	Split path by ':' to get an array per path to binaries
	Run through each binary's directory
	access() is used to check if file exists

	replace given binary (ex:ls) by its abs path (ex:bin/ls)

	building absolute path
	1. run through PATH arrays, append to empty binary_path
	2. add '/' to PATH array
	3. add input (command) entered by user (p. ex 'ls')
	4. access() check if it exists
	now we got the absolute path in binary_path
*/
static void	build_absolute_path(char *path ,char **args)
{
	char	**path_split;
	char	*binary_path;
	int		i;

	binary_path = NULL;
	path_split = NULL;
	path_split = ft_split(path, ':');
	free(path);
	path = NULL;
	i = -1;
	while (path_split[++i])
	{
		binary_path = (char *)ft_calloc(sizeof(char),
			(ft_strlen(path_split[i]) + 1 + ft_strlen(args[0]) + 1));
		if (binary_path == NULL)
			break ; // stop loop, no more path to check
		ft_strcat(binary_path, path_split[i]); // ls
		ft_strcat(binary_path, "/");
		ft_strcat(binary_path, args[0]);
		if (access(binary_path, F_OK) == 0)
			break ;
		free(binary_path);
		binary_path = NULL;
	}
	clean(path_split, args);
	args[0] = binary_path;
}

/*
	but :
	1. verifier si on nous a donne un chemin absolu vers un binaire ou pas
	si on recoit une commande 'ls', on la remplace par son emplacement absolu
	car execve() necessite un chemin absolu vers les binaires a executer.
	2. verifier si le binaire existe avec access().


*/
void	is_absolute_path(char **args, t_list *env)
{
	char	*path;

	(void)env;
	path = ft_strdup(getenv("PATH")); //attention getenv le trouvera par l'OS
	if (args[0] == NULL)
		return ;
	if (path == NULL) // si PATH unset avant...
	{
		free(path);
		return ;
	}
	if (args[0][0] != '/' && ft_strncmp(args[0], "./", 2) != 0) // si on nous a pas donne un chemin absolu
		build_absolute_path(path, args);
	else // si on nous a bien donné /bin/ls, on est pret a executer la commande via execve
	{
		free(path);
		path = NULL;
	}
}