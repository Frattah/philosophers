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
	int			tmp;

	philo = (t_philo *) arg;
	waiting(&philo->shared->stop_mutex, &philo->shared->stop);
	tmp = 0;
	i = -1;
	if (philo->phil_num == 1)
	{
		print(philo, "has taken a fork");
		my_usleep(philo->ttd * 1.2, philo->shared->init);
		return (0);
	}
	while (!tmp && (++i < philo->nme || !philo->nme))
	{
		if (philo->id % 2 == 0)
			even_routine(philo, i);
		else
			odd_routine(philo, i);
		pthread_mutex_lock(&philo->shared->stop_mutex);
		tmp = philo->shared->stop;
		pthread_mutex_unlock(&philo->shared->stop_mutex);
	}
	return (0);
}

void	odd_routine(t_philo *philo, int i)
{
	int	think_time;

	eat(philo, i);
	print(philo, "is sleeping");
	my_usleep(philo->tts, philo->shared->init);
	print(philo, "is thinking");
	think_time = philo->tte - philo->tts;
	if (think_time > 0)
		my_usleep(philo->tte - philo->tts, philo->shared->init);
}

void	even_routine(t_philo *philo, int i)
{
	int	think_time;

	print(philo, "is thinking");
	think_time = philo->tte - philo->tts;
	if (i == 0)
		think_time = philo->tte;
	if (think_time > 0)
		my_usleep(think_time, philo->shared->init);
	eat(philo, i);
	print(philo, "is sleeping");
	my_usleep(philo->tts, philo->shared->init);
}

void	death_control(t_philo **tab, t_shared *shared, int *tmp)
{
	int	i;
	int	phil_num;

	i = -1;
	phil_num = tab[0]->phil_num;
	while (++i < phil_num && *tmp == 0)
	{
		pthread_mutex_lock(&tab[i]->lst_eat_mutex);
		if (get_time(shared->init) - tab[i]->lst_eat > tab[i]->ttd
			&& tab[i]->lst_eat != -1)
		{
			pthread_mutex_unlock(&tab[i]->lst_eat_mutex);
			death(tab[i]);
		}
		else
			pthread_mutex_unlock(&tab[i]->lst_eat_mutex);
		usleep(20);
		pthread_mutex_lock(&shared->stop_mutex);
		*tmp = shared->stop;
		pthread_mutex_unlock(&shared->stop_mutex);
	}
}

void	*control_routine(void *arg)
{
	t_philo		**tab;
	t_shared	*shared;
	int			tmp;

	tab = (t_philo **) arg;
	tmp = 0;
	shared = tab[0]->shared;
	waiting(&shared->stop_mutex, &shared->stop);
	while (tmp == 0)
		death_control(tab, shared, &tmp);
	return (0);
}
