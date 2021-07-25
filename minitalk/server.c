/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: song-yejin <song-yejin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 18:54:24 by song-yejin        #+#    #+#             */
/*   Updated: 2021/07/25 22:39:35 by song-yejin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

#define BUFSIZE 2048

void	make_char(char c, int *cnt, char *s, pid_t *pid)
{
	s[*cnt] = c;
	if (c == '\0')
		*pid = 0;
	else
		(*cnt)++;
	if (c == '\0' || *cnt == BUFSIZE)
	{
		write(1, s, *cnt);
		*cnt = 0;
	}
}

int		ck_pid(pid_t *pid, pid_t inpid)
{
	if (*pid == 0)
	{
		*pid = inpid;
		kill(inpid, SIGUSR1);
	}
	else if (*pid == inpid)
		kill(inpid, SIGUSR1);
	else if (*pid != inpid)
	{
		kill(inpid, SIGUSR2);
		return (1);
	}
	return (0);
}

void	recieve(int signo, siginfo_t *info, void *none)
{
	static char		c;
	static int		i;
	static int		cnt;
	static pid_t	pid;
	static char		s[BUFSIZE];

	(void)none;
	if (ck_pid(&pid, info->si_pid))
		return ;
	if (signo == SIGUSR1)
		c |= 1 << i;
	if (i == 7)
	{
		make_char(c, &cnt, s, &pid);
		c = 0;
		i = 0;
	}
	else
		i++;
}

int	main()
{
	struct sigaction	act;

	ft_putstr_fd("Sever PID :: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	act.sa_sigaction = recieve;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}