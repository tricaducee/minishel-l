/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:19:33 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/15 03:32:55 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	prompt_cat(char *prompt, const char *element, unsigned int *i)
{
	unsigned int	j;

	if (!prompt || !element)
		return ;
	j = 0;
	while (element[j])
		prompt[(*i)++] = element[j++];
}

char	*get_git_branch(char *git_path)
{
	int		fd;
	int		rd;
	char	buff[500];

	fd = open(git_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	rd = read(fd, buff, 500);
	close(fd);
	buff[--rd] = 0;
	while (rd && buff[rd] != '/')
		rd--;
	return (ft_strdup(1 + rd + buff));
}

void	git_prompt(char *prompt, const char **prompt_elem,
			char *git_path, char *cwd)
{
	unsigned int	i;
	unsigned int	j;
	char			*branch_name;

	i = 0;
	j = 0;
	branch_name = get_git_branch(git_path);
	while (prompt_elem[i])
	{
		prompt_cat(prompt, prompt_elem[i], &j);
		if (!i)
		{
			prompt_cat(prompt, "\033[3m", &j);
			prompt_cat(prompt, cwd, &j);
		}
		else if (i == 2)
			prompt_cat(prompt, branch_name, &j);
		i++;
	}
	prompt[j] = 0;
	if (branch_name)
		free(branch_name);
}

void	none_git_prompt(char *prompt, const char **prompt_elem, char *cwd)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (prompt_elem[i])
	{
		if (i == 2)
		{
			i += 2;
			if (!prompt_elem[i])
			{
				prompt[j] = 0;
				return ;
			}
		}
		prompt_cat(prompt, prompt_elem[i], &j);
		if (!i)
		{
			prompt_cat(prompt, "\033[3m", &j);
			prompt_cat(prompt, cwd, &j);
		}
		i++;
	}
	prompt[j] = 0;
}

char	*get_git_path(char *cwd, char *file)
{
	char			*ret;
	unsigned int	i;

	ret = malloc((ft_strlen(cwd) + 11) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (*cwd)
		ret[i++] = *(cwd++);
	while (*file)
		ret[i++] = *(file++);
	ret[i] = 0;
	if (!access(ret, R_OK))
		return (ret);
	free(ret);
	return (NULL);
}
