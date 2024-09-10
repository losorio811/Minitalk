/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loosorio <loosorio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:57:21 by loosorio          #+#    #+#             */
/*   Updated: 2024/06/24 16:33:55 by loosorio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static int	ft_atoi(char *pid)
{
	int	i;
	long	res;

	i = 0;
	res = 0;
	if (!(pid[i] >= '0' && pid[i] <= '9'))
		return (-1);
	while (pid[i] >= '0' && pid[i] <= '9')
	{
		res = res * 10 + pid[i] - '0';
		i++;
	}
	return (res);
}

static void	ft_sendlen(char *str, pid_t pid)
{
	int	i;
	int	len;

	len = 0;
	i = 31;
	while (*(str++))
		len++;
	while(i >= 0)
	{
		if (len >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(100);
	}
}

static void	ft_sendchar(char *str, pid_t pid)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 7;
		while(j >= 0)
		{
			if (str[i] >> j & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
			usleep(100);
		}
		i++;
	}
	i = 7;
	while (i >= 0)
	{
		kill(pid, SIGUSR2);
		i--;
		usleep(100);
	}
	
}

int main(int argc, char *argv[])
{
	pid_t	pid;

    if (argc == 3)
    {
		pid = ft_atoi(argv[1]);
		if (pid < 1)
			exit(write(2, "Invalid PID\n", 12));
		ft_sendlen(argv[2], pid);
		ft_sendchar(argv[2], pid);
    }
	else
		return (write(2, "Error! Use: ./client PID str\n", 29));
	return (0);
}