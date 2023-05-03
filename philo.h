/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:38:28 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/03 11:51:01 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_shared
{	
	int				start_death;
	pthread_mutex_t	srt_dth_mutex;
	long long int	init;
}	t_shared;

typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	dx_fork;
	pthread_mutex_t	*sx_fork;
	t_shared		*shared;
	long long int	last_eat;
	int				stats[6];
}	t_philo;

void		*philo_routine(void *arg);

void		free_all(t_shared *shared, t_philo **tab);

t_philo		*philo_init(t_shared *shared, t_philo *philo, int arc, char **arv);

t_philo		**tab_init(t_shared *shared, int argc, char **argv);

t_shared	*shared_init(t_shared *shared);
#endif
