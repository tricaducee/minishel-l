/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:19:33 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/06 23:45:51 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*prompt_join(char *s1, char *s2, char *s3)
{
	char			*ret;
	unsigned int	i;

	ret = malloc((ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s1)
		ret[i++] = *(s1++);
	while (*s2)
		ret[i++] = *(s2++);
	while (*s3)
		ret[i++] = *(s3++);
	ret[i] = 0;
	return (ret);
}

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
			prompt_cat(prompt, cwd, &j);
		else if (i == 1)
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
		if (i == 1)
			i += 2;
		prompt_cat(prompt, prompt_elem[i], &j);
		if (!i)
			prompt_cat(prompt, cwd, &j);
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

char	*ft_prompt(void)
{
	static char		prompt[PATH_MAX + 110];
	char			cwd[PATH_MAX];
	char			*git_path;
	const char		*prompt_elem[] = {
		"\033[32m🄼  ⓘ  ⓝ  ⓘ  \033[33m🅂  ⓗ  ⓔ  ⓛ  ⓛ  🍋 \033[0;3m",
		"\033[0;32m on (\033[1;34m", "\033[0;32m)", "\n\033[1m% 👉 \033[0m", NULL};

	git_path = get_git_path(getcwd(cwd, PATH_MAX), "/.git/HEAD");
	if (git_path)
	{
		git_prompt(prompt, prompt_elem, git_path, cwd);
		free(git_path);
	}
	else
		none_git_prompt(prompt, prompt_elem, cwd);
	return (prompt);
}
