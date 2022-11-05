/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:46:34 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/05 04:17:37 by lgenevey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
#include "../../printfd/HEADER/ft_printfd.h"

/*
	handle ctrl + C (interruption)
*/
void	handle_interrupt(int sig)
{
	if (sig == SIGINT)
		ft_printfd(1, "\n%s", ft_prompt());
}

/*
	handle ctrl + \
	no ^C with ECHOCTL option
	using them
*/
void	sig_handler(t_shell *shell)
{
	struct termios	terminos;

	if (tcgetattr(0, &terminos) != 0)
		perror("tcgetattr() error");
	terminos.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminos);
	sigaction(SIGINT, &shell->sa_interrupt, NULL);
	sigaction(SIGQUIT, &shell->sa_backslash, NULL);
}
