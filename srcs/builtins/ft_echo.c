/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 00:32:45 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/11/04 04:21:59 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

typedef struct S_echoptions
{
	int	e;
	int	n;
	int	c;
}		t_echoptions;

static void	put_bs(char c)
{
	if (c == '\\')
		write(1, "\\", 1);
	else if (c == 'a')
		write(1, "\a", 1);
	else if (c == 'b')
		write(1, "\b", 1);
	else if (c == 'e')
		write(1, "\e", 1);
	else if (c == 'f')
		write(1, "\f", 1);
	else if (c == 'r')
		write(1, "\r", 1);
	else if (c == 't')
		write(1, "\t", 1);
	else if (c == 'v')
		write(1, "\v", 1);
}

static void	putstr_bs(char *s, t_echoptions *options)
{
	while (*s)
	{
		if (options->e && *s == '\\')
		{
			if (*(++s) == 'n')
			{
				if (options->c)
					write(1, "$", 1);
				write(1, "\n", 1);
			}
			else if (*s)
				put_bs(*s);
			if (*s)
				++s;
		}
		else if (options->c && *s == '\n')
			write(1, "$", 1);
		if (*s)
			write(1, s++, 1);
	}
}

void	init_options(t_echoptions *options)
{
	options->n = 0;
	options->e = 0;
	options->c = 0;
}

char	**set_options(char **ss, t_echoptions *options)
{
	unsigned int	i;

	init_options(options);
	while (*ss && (*ss)[0] == '-')
	{
		if (ft_strinset((*ss) + 1, "enc"))
			return (ss);
		i = 1;
		while ((*ss)[i] && ((*ss)[i] == 'e'
			|| (*ss)[i] == 'n' || (*ss)[i] == 'c'))
		{
			if ((*ss)[i] == 'e')
				options->e = 1;
			else if ((*ss)[i] == 'n')
				options->n = 1;
			else if ((*ss)[i] == 'c')
				options->c = 1;
			i++;
		}
		ss++;
	}
	return (ss);
}

void	ft_echo(char **ss)
{
	t_echoptions	options;

	if (!ss || !*ss)
	{
		write(1, "\n", 1);
		return ;
	}
	ss = set_options(ss, &options);
	if (*ss)
	{
		while (*ss && *(ss + 1))
		{
			putstr_bs(*(ss++), &options);
			write(1, " ", 1);
		}
		putstr_bs(*ss, &options);
	}
	if (!options.n)
	{
		if (options.c)
			write(1, "$", 1);
		write(1, "\n", 1);
	}
	g_errno = 0;
}
