/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/03 11:59:39 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(&philo->shared->srt_dth_mutex);
	tmp = philo->shared->start_death;
	pthread_mutex_unlock(&philo->shared->srt_dth_mutex);
	while (tmp == 0)
	{
		pthread_mutex_lock(&philo->shared->srt_dth_mutex);
		tmp = philo->shared->start_death;
		pthread_mutex_unlock(&philo->shared->srt_dth_mutex);
	}
	usleep(philo->stats[0] * 300);
}

void	eat_and_sleep(t_philo *philo)
{
	struct timeval	tmp;

	pthread_mutex_lock(&philo->shared->time_mutex);
	tmp = philo->shared->init;
	pthread_mutex_unlock(&philo->shared->time_mutex);
	pthread_mutex_lock(&philo->dx_fork);
	printf("%lld ms %d has taken a fork\n", get_time(tmp), philo->stats[0]);
	pthread_mutex_lock(philo->sx_fork);
	printf("%lld ms %d has taken a fork\n", get_time(tmp), philo->stats[0]);
	printf("%lld ms %d is eating\n", get_time(tmp), philo->stats[0]);
	my_usleep(philo->stats[3], tmp);
	pthread_mutex_unlock(&philo->dx_fork);
	pthread_mutex_unlock(philo->sx_fork);
	printf("%lld ms %d is sleeping\n", get_time(tmp), philo->stats[0]);
	my_usleep(philo->stats[4], tmp);
}
