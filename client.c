/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:31:50 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/28 15:30:16 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

// TODO: double check makefile
// TODO: use bzero insted of {0}

/*
	Useful info about signals:
	https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/
	Signals Info:
		- unistd.h : getpid()
		- signal.h : signals
		- 10 SIGUSR1	Terminate	User-defined signal 30
		- 12 SIGUSR2	Terminate	User-defined signal 31
		- kill(pid_t pid, int sig): send signal sig to process pid
		- use sigaction() instead of signal() for portability issues
			- define a signal hander function
			- define a list with signals to be blocked during handling
		- declare shared global variables as volatile
			- global var used assigned in hander and reader from main
			- otherwise may compiler cache them, consider they not updated
		- declare a flag with sig_atomic_t type
			- flags you read on main and set on handler to be use that \
			no other interaption between write-read them
		- sigemptyset: create empty list of signals to be blocked
		- sigaddset: add signal to list, in order to be blocked
		- act
			- act.sa_mask: function to be blocked
			- act.sa_hander: function to run when signal received
			- if act.sa_sigaction & act.sa_handler != 0 at the same time \
			there is a big problem, so initially, bzero to the whole act
		- pause() : suspend until a signal reach
		- https://man7.org/linux/man-pages/man7/signal-safety.7.html
			- signal safe functs in handlers
		- struct sigaction	act = {0}: if you forgot it, it will not work
		- when a signal is received, handler executed and then continue from \
		the last command before the signal
 */

static int	is_int(char *str, int *result);
static int	ft_atoi(const char *str);
void		handler(int signal);

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	int					j;
	int					k;

	signal(SIGUSR1, &handler);
	if (argc != 3 || !is_int(argv[1], &pid))
		return (0);
	i = 0;
	while (42)
	{
		j = 7;
		while (j >= 0)
		{
			if (((argv[2][i] >> j--) & 1) == 1)
				k = kill(pid, SIGUSR1);
			else
				k = kill(pid, SIGUSR2);
			if (k == -1)
				return (1);
			pause();
		}
		if (argv[2][i++] == '\0')
			return (0);
	}
}

void	handler(int signal)
{
	signal++;
}

static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	div;
	long	result;
	int		end;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '+') * 2 - 1;
	result = 0;
	end = i;
	while (str[end] != '\0')
		end++;
	div = 1;
	while (str[end - 1] >= '0' && str[end - 1] <= '9')
	{
		result = result - ((str[end - 1] - '0') * div);
		div *= 10;
		if (end == 1)
			break ;
		end--;
	}
	return (result * sign * -1);
}

// insteger means less than 10 digits + 1 for sign
// checks also for overflow, underflow 2147483647 -2147483648
// checks if exist characters other than digits
// returns 1 if number is integer or 0 if not
// puts the result number on &result
static int	is_int(char *str, int *result)
{
	int		i;
	long	temp;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > 11 || i == 0 || (i == 1 && (str[0] == '-' || str[0] == '+')))
		return (0);
	temp = ft_atoi(str);
	if (temp > 2147483647 || temp < -2147483648)
		return (0);
	*result = (int) temp;
	return (1);
}
