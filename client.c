/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:31:50 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/27 09:59:49 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

static int	is_int(char *str, int *result);
static int	ft_atoi(const char *str);

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	int	j;

	if (argc != 3 || !is_int(argv[1], &pid))
		return (0);
	while (42)
	{
		j = 0;
		while (j < 8)
		{
			if (argv[2][i] >> i & 1 == 1)
				if (kill(pid, SIGUSR1) == -1)
					return (1);
			else
				if (kill(pid, SIGUSR2) == -1)
					return (1);
			j++;
		}
		if (argv[2][i] != '\0')
			return (0);
		i++;
	}
}

// client
// validation_check
// 	- number of parameter == 3
// 	- 1st should be an int
// 		- convert string to int (atoi)
// 	- 2nd should be a string
// send string
// 	- for each char of string
// 		- for each bit of char(8 bits)
// 			- send SIGUSR1 if 0 or SIGUSR2 if 1

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
