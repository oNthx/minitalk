/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozgur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 03:15:51 by bozgur            #+#    #+#             */
/*   Updated: 2022/04/27 05:57:37 by bozgur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void	ifbyte(size_t *totalbyte, char *byte, size_t *circle, pid_t pid)
{
	if ((*totalbyte) >= 4)
	{
		write(1, byte, 1);
		(*circle)--;
		if (!*circle)
		{
			kill(pid, SIGUSR1);
			(*totalbyte) = -1;
		}
	}
		(*totalbyte)++;
}

void	set(int c, siginfo_t *siginfo, void *context)
{
	static char		byte;
	static char		bit;
	static size_t	circle;
	static size_t	totalbyte;

	(void)context;
	if (totalbyte < 4)
	{
		if (c == SIGUSR1)
			circle = circle | (1 << (bit + (8 * totalbyte)));
		else
			circle = circle & ~(1 << (bit + (8 * totalbyte)));
	}
	else if (c == SIGUSR1)
		byte = byte | (1 << bit);
	else
		byte = byte & ~(1 << bit);
	if (bit == 7)
		ifbyte(&totalbyte, &byte, &circle, siginfo->si_pid);
	bit = (bit + 1) % 8;
}

void	ft_putnbr(int n)
{
	if (n > 10)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = set;
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		;
}
