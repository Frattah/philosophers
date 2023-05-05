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

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *) arg;
	waiting(philo);
	i = -1;
	while (++i < philo->stats[5] || !philo->stats[5])
	{
		print(philo, "is thinking");
		eat_and_sleep(philo);
	}
	return (0);
}
