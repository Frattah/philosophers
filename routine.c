/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/05 11:56:46 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *) arg;
	waiting(&philo->shared->stop_mutex, &philo->shared->stop);
	if (philo->stats[0] % 2 == 0)
		usleep(50);
	i = -1;
	while (++i < philo->stats[5] || !philo->stats[5])
	{
		print(philo, "is thinking");
		eat_and_sleep(philo);
	}
	return (0);
}

void	*control_routine(void *arg)
{
	t_philo		**tab;
	t_shared	*shared;
	int			i;
	int			tmp;

	tab = (t_philo **) arg;
	tmp = 0;
	shared = tab[0]->shared;
	waiting(&shared->stop_mutex, &shared->stop);
	while (tmp == 0)
	{
		i = -1;
		while (++i < tab[0]->stats[1] && tmp == 0)
		{
			pthread_mutex_lock(&shared->lst_eat_mutex);
			if (get_time(shared->init) - shared->lst_eat[i] > tab[i]->stats[2])
			{
				pthread_mutex_unlock(&shared->lst_eat_mutex);
				death(tab[i]);
			}
			else
				pthread_mutex_unlock(&shared->lst_eat_mutex);
			pthread_mutex_lock(&shared->stop_mutex);
			tmp = shared->stop;
			pthread_mutex_unlock(&shared->stop_mutex);
		}	
	}
	return (0);
}
