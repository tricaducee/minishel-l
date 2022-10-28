/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:00:30 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/25 20:30:34 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char			*ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	ret = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		++i;
	}
	ret[i] = 0;
	return (ret);
}
