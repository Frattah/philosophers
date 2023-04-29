#include "philosophers.h"

int	ist_init(ist_t	**ist, int argc, char **argv)
{
	*ist = (ist_t *) malloc(sizeof(ist_t));
	if (!(*ist))
		return (error_managment(2));
	(*ist)->phil_num = atoi(argv[1]);
	(*ist)->ttd = atoi(argv[2]);
	(*ist)->tte = atoi(argv[3]);
	(*ist)->tts = atoi(argv[4]);
	if (argc == 6)
		(*ist)->nme = atoi(argv[5]);
	else
		(*ist)->nme = 0;
	if ((*ist)->phil_num <= 0 || (*ist)->ttd <= 0 || (*ist)->tte <= 0 || 
	    (*ist)->tts <= 0 || (*ist)->nme < 0)
	{
		free(*ist);
		return (error_managment(3));
	}
	(*ist)->start = 0;
	(*ist)->control = (long long int *) malloc(sizeof(long long int) * (*ist)->phil_num);
	if (!(*ist)->control)
	{
		free(*ist);
		free((*ist)->control);
		return (error_managment(2));
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
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
	while (++i < p->ist->nme || !p->ist->nme)
	{
		printf("%lld %d is thinking\n", get_time(), p->id);
		pthread_mutex_lock(p->dx_fork);
		printf("%lld %d has taken a fork\n", get_time(), p->id);
		pthread_mutex_lock(&p->sx_fork);
		printf("%lld %d has taken a fork\n", get_time(), p->id);
		printf("%lld %d is eating\n", p->ist->control[p->id - 1], p->id);
		usleep(p->ist->tte * 1000);
		p->ist->control[p->id - 1] = get_time();
		pthread_mutex_unlock(p->dx_fork);
		pthread_mutex_unlock(&p->sx_fork);
		printf("%lld %d is sleeping\n", get_time(), p->id);
		usleep(p->ist->tts * 1000);
	}
	p->ist->start = 0;
	return (0);
}

void	*control_rout(void *arg)
{
	ist_t	*ist;
	int		death;
	int		i;

	ist = (ist_t *) arg;
	death = 0;
	while (death == 0 && ist->start)
	{
		i = -1;
		while (death == 0 && ++i < ist->phil_num && ist->start)
		{
			if (get_time() - ist->control[i] > ist->ttd)
			{
				printf("%lld %d died\n", get_time(), i + 1);
				death++;
			}	
		}
	}
	i = -1;
	while (++i < ist->phil_num)
		pthread_detach(ist->tab[i]->th);
	return (0);
}

int	philo_create(philo_t **tab, ist_t *ist)
{
	int	i;
	int	*a;

	i = -1;
	while (++i < ist->phil_num)
	{
		tab[i] = (philo_t *) malloc(sizeof(philo_t));
		if (!tab[i])
			return (error_managment(2));
		if (i != 0)
			tab[i - 1]->dx_fork = &(tab[i]->sx_fork);
		if (i == ist->phil_num - 1)
			tab[i]->dx_fork = &(tab[0]->sx_fork);
	  	tab[i]->ist = ist;
		if (pthread_mutex_init(&(tab[i]->sx_fork), NULL))
			return (error_managment(5));
		tab[i]->id = i + 1;
		a = (int *) malloc(sizeof(int));
		if (!a)
			return (error_managment(2));
		if (pthread_create(&tab[i]->th, NULL, &philo_rout , (void *) tab[i]))
			return (error_managment(4));
		free(a);
	}
	ist->tab = tab;
	return (0);
}

void	free_all(ist_t *ist)
{
	int	i;

	i = -1;
	while (++i < ist->phil_num)
	{
		pthread_mutex_destroy(&ist->tab[i]->sx_fork);
		free(ist->tab[i]);
	}
	free(ist->tab);
	free(ist->control);
	free(ist);
}


int	error_managment(int error_code)
{
	if (error_code == 1)
		write(2, "Error(1): incorrect number of parameters!\n", 42);
	if (error_code == 2)
		write(2, "Error(2): malloc failed!\n", 25);
	if (error_code == 3)
		write(2, "Error(3): invalid parameters!\n", 31);
	if (error_code == 4)
		write(2, "Error(4): error in thread creation!\n", 36);
	if (error_code == 5)
		write(2, "Error(5): error in mutex initialization!\n", 41);
	if (error_code == 6)
		write(2, "Error(6): error in thread join!\n", 32);
	return (error_code);
}
   
int main(int argc, char **argv)
{
	ist_t		*ist;
	philo_t		**tab;
	pthread_t	control;
	int		i;
	int		err;

	if (argc != 6 && argc != 5)
		return (error_managment(1));
	err = ist_init(&ist, argc, argv);
	if (err)
		return (err);
	tab = (philo_t **) malloc(sizeof(philo_t *) * ist->phil_num);
	if (!tab)
		return(error_managment(2));
	
	err = philo_create(tab, ist);
	if (err)
		return (err);
	gettimeofday(&ist->time, NULL);

	printf("START %lld\n", get_time());
	ist->start = get_time();
	i = -1;
	while (++i < ist->phil_num)
		ist->control[i] = ist->start;
	
	if (pthread_create(&control, NULL, &control_rout, (void *) ist))
		return (error_managment(4));
	if (pthread_join(control, NULL))
		return (error_managment(6));
/*
	i = -1;
	while (++i < ist->phil_num)
		pthread_join(tab[i]->th, NULL);
*/
	free_all(ist);
}
