/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozgur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 02:47:19 by bozgur            #+#    #+#             */
/*   Updated: 2022/04/27 17:04:51 by bozgur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

int	ftstrlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

int	ftatoi(char *str)
{
	int	res;
	int	sgn;

	res = 0;
	sgn = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sgn = -1;
	while (*str >= '0' && *str <= '9')
		res = (res * 10) + *str++ - '0';
	return (res * sgn);
}

void	bitop(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(100);
	}
}

void	delivered(int c)
{
	(void)c;
	write(1, "Devlivered\n", 11);
	exit(0);
}

int	main(int argc, char **argv)
{
	int					pid;
	int					index;
	static size_t		bytesize;
	struct sigaction	act;
	char				*bytesize_c;

	index = 0;
	if (argc == 3)
	{
		act.sa_handler = delivered;
		sigaction(SIGUSR1, &act, 0);
		pid = ftatoi(argv[1]);
		bytesize = (size_t)ftstrlen(argv[2]) + 1;
		bytesize_c = (char *)&bytesize;
		while (index < 4)
			bitop(bytesize_c[index++], pid);
		index = 0;
		while (argv[2][index])
			bitop(argv[2][index++], pid);
		bitop('\n', pid);
	}	
	while (1)
		;
}
