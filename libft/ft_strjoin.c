/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:56:57 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 18:33:01 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ret;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	ret = str;
	if (!str)
		return (0);
	while (s1 && *s1)
		*(str++) = *(s1++);
	while (s2 && *s2)
		*(str++) = *(s2++);
	*str = 0;
	return (ret);
}
