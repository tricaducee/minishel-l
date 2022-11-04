/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 04:00:27 by hrolle            #+#    #+#             */
/*   Updated: 2022/11/04 04:11:58 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strinset(char *str, char *set)
{
	unsigned int	i;

	while (*str)
	{
		i = 0;
		while (set[i] && set[i] != *str)
			i++;
		if (!set[i])
			return (1);
		str++;
	}
	return (0);
}
