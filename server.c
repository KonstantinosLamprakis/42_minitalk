/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:31:52 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/27 12:59:26 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static void	put_nbr(long n);
static void	handle_0(int signal);
static void	handle_1(int signal);

// https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/

int	main(void)
{
	int	i;

	put_nbr(getpid());
	signal(SIGUSR1, handle_1);
	signal(SIGUSR2, handle_0);
	while (42)
	{
		usleep(10);
		break ;
		i++;
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

static void	handle_1(int signal)
{
	return ;
}

static void	handle_0(int signal)
{
	return ;
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
