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

t_phi	*phi_init(t_shared *shared, t_phi *phi, int arc, char **arv)
{
	phi = (t_phi *) malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	pthread_mutex_init(&phi->dx_fork, NULL);
	pthread_mutex_init(&phi->lst_eat_mutex, NULL);
	phi->phil_num = ft_atoi(arv[1]);
	phi->ttd = ft_atoi(arv[2]);
	phi->tte = ft_atoi(arv[3]);
	phi->tts = ft_atoi(arv[4]);
	phi->nme = 0;
	phi->lst_eat = 0;
	if (arc == 6)
		phi->nme = ft_atoi(arv[5]);
	phi->shared = shared;
	return (phi);
}

t_phi	**tab_init(t_shared *shared, int arc, char **arv)
{
	t_phi	**tab;
	int		i;
	int		phil_num;

	phil_num = ft_atoi(arv[1]);
	tab = (t_phi **) malloc(sizeof(t_phi *) * phil_num);
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < phil_num)
	{	
		tab[i] = phi_init(shared, tab[i], arc, arv);
		tab[i]->id = i + 1;
		if (i != 0)
			tab[i]->sx_fork = &tab[i - 1]->dx_fork;
		pthread_create(&tab[i]->th, NULL, &phi_routine, (void *) tab[i]);
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
