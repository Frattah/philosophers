/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:04 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/04 11:45:25 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared->print_mutex);
	printf("%lld ms %d %s\n", get_time(philo->shared->init),
		philo->stats[0], str);
	pthread_mutex_unlock(&philo->shared->print_mutex);
}
