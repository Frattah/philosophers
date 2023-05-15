/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 08:38:28 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/15 10:02:45 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>	// printf
# include <stdlib.h>	// malloc free
# include <unistd.h>	// usleep
# include <pthread.h>	// pthread_create pthread_destroy pthread_mutex_init
			// pthread_mutex_lock pthread_mutex_unlock
			// pthread_mutex_destroy
# include <sys/time.h>	// gettimeofday

// -------- Resources shared by threads ---------

typedef struct s_shared
{	
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	struct timeval	init;
}	t_shared;

// -------- phisopher structure ---------------

typedef struct s_phi
{
	pthread_t		th;
	pthread_mutex_t	dx_fork;
	pthread_mutex_t	*sx_fork;
	pthread_mutex_t	lst_eat_mutex;
	long long int	lst_eat;
	t_shared		*shared;
	int				id;
	int				phil_num;
	int				ttd;
	int				tte;
	int				tts;
	int				nme;
}	t_phi;

// -------- Action of phisophers ---------------

void			waiting(pthread_mutex_t *stop_mutex, int *stop);

void			death(t_phi *phi);

void			eat(t_phi *phi, int i);

// -------- Initialization functions -------------

t_phi			*phi_init(t_shared *shared, t_phi *phi, int arc, char **arv);

t_phi			**tab_init(t_shared *shared, int arc, char **arv);

t_shared		*shared_init(t_shared *shared);

// -------- Simulation foundamentals --------------

long long int	get_time(struct timeval init);

void			my_usleep(int mms, t_shared *shared);

void			free_all(t_shared *shared, t_phi **tab);

void			launch_simulation(t_shared *shared, t_phi **tab);

// -------- Threads routines ---------------------

void			*phi_routine(void *arg);

void			odd_routine(t_phi *phi, int i);

void			even_routine(t_phi *phi, int i);

void			death_control(t_phi **tab, t_shared *shared);

void			*control_routine(void *arg);

// -------- Utilities and error managment --------

void			print(t_phi *phi, char *str);

int				ft_atoi(const char *str);

int				ft_strncmp(const char *s1, const char *s2, int n);

int				error_managment(int argc, char **argv);

int				is_end(t_shared *shared);

#endif
