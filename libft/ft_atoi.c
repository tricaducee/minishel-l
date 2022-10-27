/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 10:10:07 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/27 00:05:11 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				pn;
	unsigned int	nbr;

	pn = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			pn *= -1;
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*(str++) - '0');
	return ((int)nbr * pn);
}
