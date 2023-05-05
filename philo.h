/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:38:28 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/05 11:57:08 by frmonfre         ###   ########.fr       */
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
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	lst_eat_mutex;
	struct timeval	init;
	long long int	*lst_eat;
}	t_shared;

typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	dx_fork;
	pthread_mutex_t	*sx_fork;
	t_shared		*shared;
	int				stats[6];
}	t_philo;

void			*philo_routine(void *arg);

void			*control_routine(void *arg);

void			free_all(t_shared *shared, t_philo **tab);

void			my_usleep(int mms, struct timeval init);

long long int	get_time(struct timeval init);

t_philo			*philo_init(t_shared *s, t_philo *p, int a, char **c);

t_philo			**tab_init(t_shared *shared, int argc, char **argv);

t_shared		*shared_init(t_shared *shared, int phil_num);

void			waiting(pthread_mutex_t *stop_mutex, int *stop);

void			eat_and_sleep(t_philo *philo);

void			death(t_philo *philo);

void			print(t_philo *philo, char *str);
#endif
