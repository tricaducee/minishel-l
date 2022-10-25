/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_uppercase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:26:08 by lgenevey          #+#    #+#             */
/*   Updated: 2022/10/25 20:27:00 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	returns 0 if a letter is not uppercase
	returns 1 if all letters are uppercase
*/
int	ft_is_uppercase(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str <= 'A' || *str >= 'Z')
			return (0);
		++str;
	}
	return (1);
}
