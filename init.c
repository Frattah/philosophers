/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:38:48 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/05 11:57:36 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(t_shared *shared, t_philo *philo, int arc, char **arv)
{
	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	pthread_mutex_init(&philo->dx_fork, NULL);
	pthread_mutex_init(&philo->lst_eat_mutex, NULL);
	philo->stats[1] = ft_atoi(arv[1]);
	philo->stats[2] = ft_atoi(arv[2]);
	philo->stats[3] = ft_atoi(arv[3]);
	philo->stats[4] = ft_atoi(arv[4]);
	philo->lst_eat = 0;
	if (arc == 6)
		philo->stats[5] = ft_atoi(arv[5]);
	philo->shared = shared;
	return (philo);
}

t_philo	**tab_init(t_shared *shared, int arc, char **arv)
{
	t_philo	**tab;
	int		i;
	int		phil_num;

	phil_num = atoi(arv[1]);
	tab = (t_philo **) malloc(sizeof(t_philo *) * phil_num);
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < phil_num)
	{	
		tab[i] = philo_init(shared, tab[i], arc, arv);
		tab[i]->stats[0] = i + 1;
		if (i != 0)
			tab[i]->sx_fork = &tab[i - 1]->dx_fork;
		pthread_create(&tab[i]->th, NULL, &philo_routine, (void *) tab[i]);
	}
	tab[0]->sx_fork = &tab[phil_num - 1]->dx_fork;
	return (tab);
}

t_shared	*shared_init(t_shared *shared)
{
	shared = (t_shared *) malloc(sizeof(t_shared));
	if (!shared)
		return (NULL);
	shared->stop = 1;
	pthread_mutex_init(&shared->stop_mutex, NULL);
	pthread_mutex_init(&shared->print_mutex, NULL);
	return (shared);
}
