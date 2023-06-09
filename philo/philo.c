/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:35:02 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/15 09:55:01 by frmonfre         ###   ########.fr       */
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

void	my_usleep(int mms, t_shared *shared)
{
	long long int	ref;

	ref = get_time(shared->init);
	while (!is_end(shared) && get_time(shared->init) - ref < mms)
		usleep(10);
}

void	free_all(t_shared *shared, t_phi **tab)
{
	int	i;
	int	phil_num;

	i = -1;
	phil_num = tab[0]->phil_num;
	while (++i < phil_num)
	{
		pthread_mutex_destroy(&tab[i]->dx_fork);
		pthread_mutex_destroy(&tab[i]->lst_eat_mutex);
		free(tab[i]);
	}
	free(tab);
	pthread_mutex_destroy(&shared->stop_mutex);
	pthread_mutex_destroy(&shared->print_mutex);
	free(shared);
}

void	launch_simulation(t_shared *shared, t_phi **tab)
{
	int			phil_num;
	int			i;
	pthread_t	control;

	phil_num = tab[0]->phil_num;
	pthread_create(&control, NULL, &control_routine, (void *) tab);
	pthread_mutex_lock(&shared->stop_mutex);
	shared->stop = 0;
	gettimeofday(&shared->init, NULL);
	pthread_mutex_unlock(&shared->stop_mutex);
	i = -1;
	while (++i < phil_num)
		pthread_join(tab[i]->th, NULL);
	pthread_mutex_lock(&shared->stop_mutex);
	shared->stop = 1;
	pthread_mutex_unlock(&shared->stop_mutex);
	pthread_join(control, NULL);
}

int	main(int argc, char **argv)
{
	t_shared	*shared;
	t_phi		**tab;

	if (error_managment(argc, argv))
		return (1);
	shared = NULL;
	shared = shared_init(shared);
	if (!shared)
		return (1);
	tab = tab_init(shared, argc, argv);
	launch_simulation(shared, tab);
	free_all(shared, tab);
}
