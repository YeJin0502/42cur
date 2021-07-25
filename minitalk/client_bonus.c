/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 16:59:20 by song-yejin        #+#    #+#             */
/*   Updated: 2021/07/25 19:35:33 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"

#define SLEEPTIME 1000

unsigned long	bit;

void	handler_sig(int signo)
{
	if (signo == SIGUSR1)
		bit++;
	else
		ft_exit("ERROR\n");
}

void	send_char(pid_t pid, char c)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < 8)
	{
		if (c & (1 << i))
			ret = kill(pid, SIGUSR1);
		else
			ret = kill(pid, SIGUSR2);
		usleep(SLEEPTIME);
		if (ret == RET_ERROR)
			ft_exit("KILL ERRROR\n");
	}
}

void	send_msg(pid_t pid, char *s)
{
	const int len = ft_strlen(s);
	int	i;

	i = -1;
	while (++i <= len)
		send_char(pid, s[i]);
}

int	ck_ag(int ac, char **ag)
{
	if (ac != 3)
		ft_exit("CHECK ARG\n");
	return (ft_atoi(&ag[1]));
}

int	main(int ac, char **ag)
{
	pid_t	pid;

	signal(SIGUSR1, handler_sig);
	signal(SIGUSR2, handler_sig);
	pid = ck_ag(ac, ag);
	send_msg(pid, ag[2]);
	if (bit == (ft_strlen(ag[2]) + 1) * 8)
		ft_putstr_fd("SUCESS\n", 1);
	else
		ft_putstr_fd("FAIL\n", 1);
}