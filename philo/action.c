/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/15 09:48:24 by frmonfre         ###   ########.fr       */
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

void	death(t_phi *phi)
{
	pthread_mutex_lock(&phi->shared->print_mutex);
	pthread_mutex_lock(&phi->shared->stop_mutex);
	printf("%lld %d is died\n", get_time(phi->shared->init), phi->id);
	phi->shared->stop = 1;
	pthread_mutex_unlock(&phi->shared->stop_mutex);
	pthread_mutex_unlock(&phi->shared->print_mutex);
}

void	eat(t_phi *phi, int i)
{
	pthread_mutex_lock(&phi->dx_fork);
	print(phi, "has taken a fork");
	pthread_mutex_lock(phi->sx_fork);
	print(phi, "has taken a fork");
	print(phi, "is eating");
	my_usleep(phi->tte, phi->shared);
	pthread_mutex_lock(&phi->lst_eat_mutex);
	if (i == phi->nme - 1)
		phi->lst_eat = -1;
	else
		phi->lst_eat = get_time(phi->shared->init);
	pthread_mutex_unlock(&phi->lst_eat_mutex);
	pthread_mutex_unlock(phi->sx_fork);
	pthread_mutex_unlock(&phi->dx_fork);
}
