/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loosorio <loosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:33 by loosorio          #+#    #+#             */
/*   Updated: 2024/06/24 16:55:55 by loosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static	int	bits_counter;

static	void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	while (*str)
		write(1, str++, 1);
}

static	void	ft_putnbr(int pid)
{
	if (pid > 9)
	{
		ft_putnbr(pid / 10);
		ft_putchar(pid % 10 + '0');
	}
	else
		ft_putchar(pid + '0');
}

static	void	ft_alloc(char **str, int len)
{
	*str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		exit (1);
	(*str)[len] = 0;
}

void	ft_resetstr(char *str, int *len, int *j)
{
	bits_counter = 0;
	*len = 0;
	*j = 0;
	ft_putstr(str);
	write(1, "\n", 1);
	free(str);
}	

static	void	handle_signal(int signal)
{
	static	int	len;
	static	int	i;
	static	int	j;
	static	char	*str;
	static	char	c;

	if (bits_counter++ < 32)
		len = (len << 1) + (signal >> 1 & 1);
	else
	{
		if (bits_counter == 33)
			ft_alloc(&str, len);
		i++;
		c = (c << 1) + (signal >> 1 & 1);
		if (i == 8)
		{
			str[j++] = c;
			if (!c)
				ft_resetstr(str, &len, &j);
			c = 0;
			i = 0;
		}
	}
}

int main()
{
    pid_t				process_id;
    struct sigaction	sa;
    
	sa.sa_handler = (void *) &handle_signal;
	sa.sa_flags = 0;
    process_id = getpid();
	ft_putnbr(process_id);
	ft_putchar('\n');
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
	{
		write(1, "Closing server\n", 15);
		exit(0);
	}
	while (1)
		usleep(9999);
	return (0);
}
