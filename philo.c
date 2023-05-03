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

long long int	get_time(long long int init)
{
	struct timeval	time;
	long long int	actual;

	gettimeofday(&time, NULL);
	actual = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (actual - init);
}

void	my_usleep(int mms, long long int init)
{
	while (get_time(init) - init != mms)
		usleep(10);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			tmp;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->shared->srt_dth_mutex);
	tmp = philo->shared->start_death == 0;
	pthread_mutex_unlock(&philo->shared->srt_dth_mutex);
	while (tmp)
	{
		pthread_mutex_lock(&philo->shared->srt_dth_mutex);
		tmp = philo->shared->start_death == 0;
		pthread_mutex_unlock(&philo->shared->srt_dth_mutex);
	}
	printf("Ciao sono un filosofo\n");
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
	free(shared);
}

int	main(int argc, char **argv)
{
	t_shared		*shared;
	struct timeval	time;
	int				i;
	t_philo			**tab;

	shared = NULL;
	shared = shared_init(shared);
	if (!shared)
		return (1);
	tab = tab_init(shared, argc, argv);
	i = -1;
	pthread_mutex_lock(&shared->srt_dth_mutex);
	gettimeofday(&time, NULL);
	shared->init = time.tv_sec * 1000 + time.tv_usec / 1000;
	shared->start_death = 1;
	pthread_mutex_unlock(&shared->srt_dth_mutex);
	while (++i < atoi(argv[1]))
	{	
		pthread_join(tab[i]->th, NULL);
	}
	printf("%lld ms\n", get_time(shared->init));
	free_all(shared, tab);
}
