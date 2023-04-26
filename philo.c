#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <sys/time.h>

typedef struct ist_s
{
	int	phil_num;
	int	ttd;
	int	tte;
	int	tts;
	int	nme;
	int	start;
	struct timeval time;
	int	*control;
}	ist_t;

typedef struct philo_s
{
	pthread_t		th;
	pthread_mutex_t	sx_fork;
	pthread_mutex_t *dx_fork;
	ist_t			*ist;
	int				id;
}	philo_t;

void	ist_init(ist_t	**ist, char **argv)
{
	*ist = (ist_t *) malloc(sizeof(ist_t));
	if (!ist)
		exit(1);
	(*ist)->phil_num = atoi(argv[1]);
	(*ist)->ttd = atoi(argv[2]);
	(*ist)->tte = atoi(argv[3]);
	(*ist)->tts = atoi(argv[4]);
	(*ist)->nme = atoi(argv[5]);
	(*ist)->start = 0;
	(*ist)->control = (int *) malloc(sizeof(int) * (*ist)->phil_num);
}

void	*philo_rout(void *arg)
{
	philo_t	*p;
	int		i;

	p = (philo_t *) arg;
	while (!p->ist->start) {}
	if (p->id % 2 == 0)
		usleep(200);
	i = -1;
	while (++i < p->ist->nme)
	{
		pthread_mutex_lock(p->dx_fork);
		printf("Il filosofo %d ha preso la forchetta destra\n", p->id);
		pthread_mutex_lock(&p->sx_fork);
		printf("Il filosofo %d ha preso la forchetta sinistra\n", p->id);
		usleep(p->ist->tte);
		printf("[?]\n");
		gettimeofday(&p->ist->time, NULL);
		p->ist->control[p->id - 1] = p->ist->time.tv_usec;
		printf("Il filosofo %d ha mangiato (%d)\n", p->id, p->ist->time.tv_usec);
		pthread_mutex_unlock(p->dx_fork);
		printf("Il filosofo %d ha posato la forchetta destra\n", p->id);
		pthread_mutex_unlock(&p->sx_fork);
		printf("Il filosofo %d ha posato la forchetta sinistra\n", p->id);
		printf("Il filosofo %d ha iniziato a dormire\n", p->id);
		usleep(p->ist->tts);
		printf("Il filosofo %d si e' svegliato\n", p->id);
		printf("Il filosofo %d pensa\n", p->id);
	}
	return (0);
}

void	*control_rout(void *arg)
{
	ist_t	*ist;
	int		death;
	int		i;

	ist = (ist_t *) arg;
	death = 0;
	while (death == 0)
	{
		i = -1;
			printf("ciaooooooo\n");
		while (death == 0 && ++i < ist->phil_num)
		{
			gettimeofday(&ist->time, NULL);
			if (ist->time.tv_usec - ist->control[i] > ist->ttd)
			{
				printf("Il filosofo %d e' morto\n", i + 1);
				death++;
			}	
		}
	}
	return (0);
}

void	philo_create(philo_t **tab, ist_t *ist)
{
	int	i;
	int	*a;

	i = 0;
	while (i < ist->phil_num)
	{
		tab[i] = (philo_t *) malloc(sizeof(philo_t));
		if (!tab[i])
			exit(1);
		if (i != 0)
			tab[i - 1]->dx_fork = &tab[i]->sx_fork;
		if (i == ist->phil_num - 1)
			tab[i]->dx_fork = &tab[0]->sx_fork;
	    tab[i]->ist = ist;
		pthread_mutex_init(&tab[i]->sx_fork, NULL);
		tab[i]->id = i + 1;
		a = (int *) malloc(sizeof(int));
		if (!a)
			exit(1);
		pthread_create(&tab[i]->th, NULL, &philo_rout , (void *) tab[i]);
		i++;
	}
}

void	free_all(ist_t *ist, philo_t **tab)
{
	int	i;

	i = -1;
	while (++i < ist->phil_num)
		free(tab[i]);
	free(tab);
	free(ist->control);
	free(ist);
}

   
int main(int argc, char **argv)
{
	ist_t	*ist;
	philo_t	**tab;
	pthread_t	control;
	int		i;

	if (argc != 6)
	{
		printf("Numero parametri non corretto!\n");
		exit(1);
	}
	ist_init(&ist, argv);
	tab = (philo_t **) malloc(sizeof(philo_t *) * ist->phil_num);
	if (!tab)
		exit(1);
	philo_create(tab, ist);
	gettimeofday(&ist->time, NULL);
	printf("START %d\n", ist->time.tv_usec);
	ist->start = ist->time.tv_usec;
	i = 0;
	pthread_create(&control, NULL, &control_rout, NULL);
	while (i < ist->phil_num)
	{
		if (pthread_join(tab[i]->th, NULL))
			return (1);
		i++;
	}
	pthread_join(control, NULL);
	free_all(ist, tab);
}
