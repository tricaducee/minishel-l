/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:41:28 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/24 18:35:21 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_my_strchr(char *s, char *c)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c[j] && c[j])
			j++;
		if (!c[j])
			return (s + i);
		else
			i++;
	}
	return (0);
}

char	*ft_my_strrchr(char *s, char *c)
{
	int	slength;
	int	i;

	slength = ft_strlen(s);
	while (slength > 0)
	{
		i = 0;
		while (s[slength] != c[i] && c[i])
			i++;
		if (s[slength] == c[i])
			slength--;
		else
			return (s + slength);
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	char	*start;
	char	*end;
	int		i;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_my_strchr((char *)s1, (char *)set);
	end = ft_my_strrchr((char *)s1, (char *)set);
	if (!start && !end)
		return (ft_strdup(""));
	str = (char *)malloc((end - start + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < end - start + 1)
		str[i] = *(start + i);
	str[i] = 0;
	return (str);
}
