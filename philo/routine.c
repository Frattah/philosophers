/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/15 09:50:18 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*phi_routine(void *arg)
{
	t_phi		*phi;
	int			i;

	phi = (t_phi *) arg;
	waiting(&phi->shared->stop_mutex, &phi->shared->stop);
	i = -1;
	if (phi->phil_num == 1)
	{
		print(phi, "has taken a fork");
		my_usleep(phi->ttd * 1.2, phi->shared);
		return (0);
	}
	while (!is_end(phi->shared) && (++i < phi->nme || !phi->nme))
	{
		if (phi->id % 2 == 0)
			even_routine(phi, i);
		else
			odd_routine(phi, i);
	}
	return (0);
}

void	odd_routine(t_phi *phi, int i)
{
	int	think_time;

	eat(phi, i);
	print(phi, "is sleeping");
	my_usleep(phi->tts, phi->shared);
	print(phi, "is thinking");
	think_time = phi->tte - phi->tts;
	if (think_time > 0)
		my_usleep(phi->tte - phi->tts, phi->shared);
}

void	even_routine(t_phi *phi, int i)
{
	int	think_time;

	print(phi, "is thinking");
	think_time = phi->tte - phi->tts;
	if (i == 0)
		think_time = phi->tte;
	if (think_time > 0)
		my_usleep(think_time, phi->shared);
	eat(phi, i);
	print(phi, "is sleeping");
	my_usleep(phi->tts, phi->shared);
}

void	death_control(t_phi **tab, t_shared *shared)
{
	int	i;
	int	phil_num;

	i = -1;
	phil_num = tab[0]->phil_num;
	while (++i < phil_num && !is_end(shared))
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
	}
}

void	*control_routine(void *arg)
{
	t_phi		**tab;
	t_shared	*shared;

	tab = (t_phi **) arg;
	shared = tab[0]->shared;
	waiting(&shared->stop_mutex, &shared->stop);
	while (!is_end(shared))
		death_control(tab, shared);
	return (0);
}
