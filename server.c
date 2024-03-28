/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:31:52 by klamprak          #+#    #+#             */
/*   Updated: 2024/03/28 15:22:54 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static void	put_nbr(long n);
void		handler(int signal, siginfo_t *info, void *ucontext);
void		*ft_memset(void *b, int c, size_t len);

int	main(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
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
		pause();
}

void	handler(int signal, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0;
	static int				count = 0;

	count++;
	ucontext = NULL;
	if (signal == SIGUSR1)
		c = (c << 1) | 1;
	else
		c = (c << 1);
	if (count == 8)
	{
		write(1, &c, sizeof(char));
		count = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

// just prints the number n
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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*result;

	i = 0;
	result = (unsigned char *)b;
	while (i < len)
	{
		result[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
