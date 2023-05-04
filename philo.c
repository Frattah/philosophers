/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/04 10:28:58 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(struct timeval init)
{
	struct timeval	actual;
	long long int	actual_mms;
	long long int	init_mms;

	gettimeofday(&actual, NULL);
	init_mms = init.tv_sec * 1000 + init.tv_usec / 1000;
	actual_mms = actual.tv_sec * 1000 + actual.tv_usec / 1000;
	return (actual_mms - init_mms);
}

void	my_usleep(int mms, struct timeval init)
{
	long long int	ref;

	ref = get_time(init);
	while (get_time(init) - ref != mms)
		usleep(10);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *) arg;
	waiting(philo);
	i = -1;
	while (++i < philo->stats[5] || !philo->stats[5])
	{
		printf("%lld ms: %d is thinking\n",
			get_time(philo->shared->init), philo->stats[0]);
		eat_and_sleep(philo);
	}
	return (0);
}

void	free_all(t_shared *shared, t_philo **tab)
{
	int	i;
	int	phil_num;

	i = -1;
	phil_num = tab[0]->stats[1];
	while (++i < phil_num)
	{
		pthread_mutex_destroy(&tab[i]->dx_fork);
		free(tab[i]);
	}
	free(tab);
	pthread_mutex_destroy(&shared->srt_dth_mutex);
	pthread_mutex_destroy(&shared->time_mutex);
	free(shared);
}

int	main(int argc, char **argv)
{
	t_shared	*shared;
	int			i;
	t_philo		**tab;

	shared = NULL;
	shared = shared_init(shared);
	if (!shared)
		return (1);
	tab = tab_init(shared, argc, argv);
	i = -1;
	pthread_mutex_lock(&shared->srt_dth_mutex);
	gettimeofday(&shared->init, NULL);
	shared->start_death = 1;
	pthread_mutex_unlock(&shared->srt_dth_mutex);
	while (++i < atoi(argv[1]))
	{	
		pthread_join(tab[i]->th, NULL);
	}
	free_all(shared, tab);
}
