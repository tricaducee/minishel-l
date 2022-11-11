/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgenevey <lgenevey@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:46:34 by lgenevey          #+#    #+#             */
/*   Updated: 2022/11/07 20:39:27 by lgenevey         ###   ########.fr       */
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
	{
		ft_printfd(1, "\n%s", ft_prompt());
		//rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
	handle ctrl + \
	no ^C with ECHOCTL option
*/
void	sig_handler(t_shell *shell)
{
	struct termios	term_flag;

	if (tcgetattr(0, &term_flag) != 0)
		perror("tcgetattr() error");
	term_flag.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term_flag);
	sigaction(SIGINT, &shell->sa_interrupt, NULL);
	sigaction(SIGQUIT, &shell->sa_backslash, NULL);
}
