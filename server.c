/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:31:52 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/28 14:44:59 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>


static void	put_nbr(long n);
void	handler(int signal, siginfo_t *info, void *ucontext);

int	main(void)
{
	struct sigaction	act = {0};

	if (sigemptyset(&act.sa_mask) == -1)
		return (1);
	if (sigaddset(&act.sa_mask, SIGUSR1) == -1)
		return (1);
	if (sigaddset(&act.sa_mask, SIGUSR2) == -1)
		return (1);
	put_nbr(getpid());
	act.sa_sigaction = &handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	act.sa_flags = SA_SIGINFO;
	while (42)
	{
		write(1, "loop\n", 5);
		pause();
	}
}

// server
// 	- bit = 0;
// 	- while (42)
// 		- for each signal
// 			- block the other signal for not interuption
// 			- add the bit to char
// 			- bit_num++
// 		- if bit_num == 8
// 			- add char to string
// 			bit_num = 0;
// 			- if char == '\0'
// 				= print the whole string
// 				= free mem of static and make it null
// 		- sleep for 1 msec

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGUSR1)
		write(1, "signal 1\n", 9);
	else if (signal == SIGUSR2)
		write(1, "signal 2\n", 9);
	kill(info->si_pid, SIGUSR1);
}

static void	put_nbr(long n)
{
	long	div;
	long	temp_num;
	char	c;

	if (n < 0)
	{
		n = -n;
		write(1, "-", sizeof(char));
	}
	temp_num = n;
	div = 1;
	while (temp_num / 10 != 0)
	{
		temp_num /= 10;
		div *= 10;
	}
	while (div >= 1)
	{
		c = '0' + (n / div);
		write(1, &c, sizeof(char));
		n %= div;
		div /= 10;
	}
	c = '\0';
	write(1, &c, sizeof(char));
}
