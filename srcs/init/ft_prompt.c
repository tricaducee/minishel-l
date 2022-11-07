/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 00:43:49 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/07 00:44:14 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
