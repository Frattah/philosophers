/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/05 11:57:55 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(pthread_mutex_t *stop_mutex, int *stop)
{
	int	tmp;

	pthread_mutex_lock(stop_mutex);
	tmp = *stop;
	pthread_mutex_unlock(stop_mutex);
	while (tmp == 1)
	{
		pthread_mutex_lock(stop_mutex);
		tmp = *stop;
		pthread_mutex_unlock(stop_mutex);
	}
}

void	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->stop_mutex);
	philo->shared->stop = 1;
	pthread_mutex_lock(&philo->shared->stop_mutex);
	print(philo, "is dead");
}

void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->dx_fork);
	print(philo, "has taken a fork");
	pthread_mutex_lock(philo->sx_fork);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	my_usleep(philo->stats[3], philo->shared->init);
	pthread_mutex_unlock(&philo->dx_fork);
	pthread_mutex_unlock(philo->sx_fork);
	pthread_mutex_lock(&philo->shared->lst_eat_mutex);
	philo->shared->lst_eat[philo->stats[0] - 1] = get_time(philo->shared->init);
	pthread_mutex_unlock(&philo->shared->lst_eat_mutex);
	print(philo, "is sleeping");
	my_usleep(philo->stats[4], philo->shared->init);
}
