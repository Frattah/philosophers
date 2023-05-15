/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:04 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/15 09:45:49 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	print(t_phi *phi, char *str)
{
	pthread_mutex_lock(&phi->shared->print_mutex);
	if (is_end(phi->shared))
	{
		pthread_mutex_unlock(&phi->shared->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", get_time(phi->shared->init),
		phi->id, str);
	pthread_mutex_unlock(&phi->shared->print_mutex);
	return ;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	meno;

	meno = 1;
	nb = 0;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (!ft_strncmp(str + i, "-2147483648", 12))
		return (-2147483648);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			meno *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > 2147483647 / 10 || nb * 10 > 2147483647 - str[i] + '0')
		{
			return (0);
		}
		nb = (nb * 10) + str[i++] - '0';
	}
	return (meno * nb);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	error_managment(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (write (2, "Error: Invalid number of parameters\n", 37));
	while (--argc)
	{
		if (ft_atoi(argv[argc]) <= 0)
			return (write(2, "Error: Invalid parameter\n", 25));
		i = -1;
		while (argv[argc][++i] != '\0')
		{	
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
				return (write(2, "Error: Invalid parameter\n", 25));
		}
	}
	return (0);
}

int	is_end(t_shared	*shared)
{
	int	tmp;

	pthread_mutex_lock(&shared->stop_mutex);
	tmp = shared->stop;
	pthread_mutex_unlock(&shared->stop_mutex);
	return (tmp);
}
