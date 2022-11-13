/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnotinset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:17:04 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/13 16:39:05 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnotinset(char *str, char *set)
{
	unsigned int	i;

	while (*str)
	{
		i = 0;
		while (set[i] && set[i] != *str)
			i++;
		if (set[i])
			return (0);
		str++;
	}
	return (1);
}
