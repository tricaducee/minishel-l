/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:19:33 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/05 01:29:38 by hrolle           ###   ########.fr       */
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

char	*ft_prompt(void)
{
	static char	*prompt;
	char		buff[PATH_MAX];

	if (prompt)
		free(prompt);
	prompt = prompt_join("\033[32m🄼  ⓘ  ⓝ  ⓘ  \033[33m🅂  ⓗ  ⓔ  ⓛ  ⓛ  🍋 \033[0;3m",
			getcwd(buff, PATH_MAX), "\n\033[1m% 👉 \033[0m");
	return (prompt);
}
