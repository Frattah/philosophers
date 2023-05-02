#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct philo_s philo_t;

typedef struct ist_s
{
	long long int	start;
	struct timeval	init;
	long long int	*control;
	philo_t		**tab;
	int		phil_num;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	control_mutex;
	pthread_mutex_t	time_mutex;
	int		ttd;
}	ist_t;

typedef struct philo_s
{
	pthread_t		th;
	pthread_mutex_t	sx_fork;
	pthread_mutex_t *dx_fork;
	ist_t			*ist;
	int				id;
	int		phil_num;
	int		ttd;
	int		tte;
	int		tts;
	int		nme;
}	philo_t;

int	ist_init(ist_t	**ist, int argc, char **argv);

void	*philo_rout(void *arg);

void	*control_rout(void *arg);

int	philo_create(philo_t **tab, ist_t *ist, int argc, char **argv);

int	free_all(ist_t *ist, philo_t **tab);

int	error_managment(int error_code);
