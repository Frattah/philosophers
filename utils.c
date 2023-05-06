/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:04 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/05 11:10:57 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

int	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared->print_mutex);
	if (strcmp(str, "died"))
		pthread_mutex_lock(&philo->shared->stop_mutex);
	if (philo->shared->stop == 1)
	{
		pthread_mutex_unlock(&philo->shared->stop_mutex);
		pthread_mutex_unlock(&philo->shared->print_mutex);
		return (1);
	}
	if (strcmp(str, "died"))
		pthread_mutex_unlock(&philo->shared->stop_mutex);
	printf("%lld %d %s\n", get_time(philo->shared->init),
		philo->id, str);
	pthread_mutex_unlock(&philo->shared->print_mutex);
	return (0);
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
