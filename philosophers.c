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
	(*ist)->nme = 0;
	if (argc == 6)
		(*ist)->nme = atoi(argv[5]);
	if ((*ist)->phil_num <= 0 || (*ist)->ttd <= 0 || (*ist)->tte <= 0 || 
	    (*ist)->tts <= 0 || (*ist)->nme < 0)
	{
		free(*ist);
		return (error_managment(3));
	}
	(*ist)->start = -1;
	gettimeofday(&(*ist)->init, NULL);
	(*ist)->control = (long long int *) malloc(sizeof(long long int) * (*ist)->phil_num);
	if (!(*ist)->control)
	{
		free(*ist);
		free((*ist)->control);
		return (error_managment(2));
	}
	return (0);
}

long long       get_time(struct timeval init)
{
        struct timeval  timeval;

        gettimeofday(&timeval, NULL);
        return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - init.tv_sec * 1000 - init.tv_usec / 1000);
}

void	*philo_rout(void *arg)
{
	philo_t	*p;
	int		i;

	p = (philo_t *) arg;
	while (p->ist->start == -1) {}
	if (p->id % 2 == 0 && p->id != p->ist->phil_num - 1)
		usleep(2);
	if (p->id != p->ist->phil_num - 1)
		usleep(3);
	i = -1;
	while (++i < p->ist->nme || !p->ist->nme)
	{
		printf("%lldms %d is thinking\n", get_time(p->ist->init), p->id);
		pthread_mutex_lock(p->dx_fork);
		printf("%lldms %d has taken a fork\n", get_time(p->ist->init), p->id);
		pthread_mutex_lock(&p->sx_fork);
		printf("%lldms %d has taken a fork\n", get_time(p->ist->init), p->id);
		printf("%lldms %d is eating\n", get_time(p->ist->init), p->id);
		usleep(p->ist->tte * 1000);
		p->ist->control[p->id - 1] = get_time(p->ist->init);
		pthread_mutex_unlock(p->dx_fork);
		pthread_mutex_unlock(&p->sx_fork);
		printf("%lldms %d is sleeping\n", get_time(p->ist->init), p->id);
		usleep(p->ist->tts * 1000);
	}
	printf("mannaggia la madonna\n");
	if (p->id != p->ist->phil_num - 1)
		p->ist->start = 0;
	return (0);
}

void	*control_rout(void *arg)
{
	ist_t	*ist;
	int		i;

	ist = (ist_t *) arg;
	while (ist->start != -1)
	{
		i = -1;
		while (++i < ist->phil_num && ist->start != -1)
		{
			//printf("%lld - %lld < %d\n", get_time(ist->init), ist->control[i], ist->ttd);
			if (get_time(ist->init) - ist->control[i] > ist->ttd)
			{
				ist->nme = -1;
				printf("%lldms %d died\n", get_time(ist->init), i + 1);
				return (0);
			}	
		}
	}
	return (0);
}

int	philo_create(philo_t **tab, ist_t *ist)
{
	int	i;

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
		if (pthread_create(&tab[i]->th, NULL, &philo_rout , (void *) tab[i]))
			return (error_managment(4));
	}
	ist->tab = tab;
	return (0);
}

int	free_all(ist_t *ist, philo_t **tab)
{
	int	i;

	i = -1;
	while (++i < ist->phil_num)
		pthread_join(tab[i]->th, NULL);
	i = -1;
	printf("\n");
	while (++i < ist->phil_num)
	{
		if (pthread_mutex_destroy(&(tab[i]->sx_fork)))
			return (error_managment(7));
		if (pthread_mutex_destroy(&(tab[i]->life)))
			return (error_managment(7));
		free(tab[i]);
	}
	free(tab);
	free(ist->control);
	free(ist);
	return (0);
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
	if (error_code == 7)
		write(2, "Error(7): error in mutex destruction\n", 38);
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

	if (pthread_create(&control, NULL, &control_rout, (void *) ist))
		return (error_managment(4));
	ist->start = get_time(ist->init);
//	printf("START %lldms\n", ist->start);
	i = -1;
	while (++i < ist->phil_num)
		ist->control[i] = ist->start;

	if (pthread_join(control, NULL))
		return (error_managment(6));
	if (free_all(ist, tab))
		return (error_managment(7));
}
