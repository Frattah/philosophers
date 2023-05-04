/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/04 10:28:19 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiting(t_philo *philo)
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
	if (philo->stats[0] % 2 == 0)
		usleep(philo->stats[3] / 10);
}

void	eat_and_sleep(t_philo *philo)
{
	struct timeval	init;
	int				id;

	init = philo->shared->init;
	id = philo->stats[0];
	pthread_mutex_lock(&philo->dx_fork);
	printf("%lld ms %d has taken a fork\n", get_time(init), id);
	pthread_mutex_lock(philo->sx_fork);
	printf("%lld ms %d has taken a fork\n", get_time(init), id);
	printf("%lld ms %d is eating\n", get_time(init), id);
	my_usleep(philo->stats[3], init);
	pthread_mutex_unlock(&philo->dx_fork);
	pthread_mutex_unlock(philo->sx_fork);
	printf("%lld ms %d is sleeping\n", get_time(init), id);
	my_usleep(philo->stats[4], init);
}
