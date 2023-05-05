/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/04 11:51:37 by frmonfre         ###   ########.fr       */
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
	pthread_mutex_destroy(&shared->print_mutex);
	free(shared);
}

int	main(int argc, char **argv)
{
	t_shared	*shared;
	t_philo		**tab;
	int			i;

	shared = NULL;
	shared = shared_init(shared);
	if (!shared)
		return (1);
	tab = tab_init(shared, argc, argv);
	pthread_mutex_lock(&shared->srt_dth_mutex);
	shared->start_death = 1;
	gettimeofday(&shared->init, NULL);
	pthread_mutex_unlock(&shared->srt_dth_mutex);
	i = -1;
	while (++i < atoi(argv[1]))
		pthread_join(tab[i]->th, NULL);
	free_all(shared, tab);
}
