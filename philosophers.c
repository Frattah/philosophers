/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:43:00 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/02 11:53:11 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ist_init(ist_t	**ist, char **argv)
{
	*ist = (ist_t *) malloc(sizeof(ist_t));
	if (!(*ist))
		return (error_managment(2));
	(*ist)->phil_num = atoi(argv[1]);
	(*ist)->ttd = atoi(argv[2]);
	(*ist)->start = -1;
	(*ist)->control = (long long int *) malloc(sizeof(long long int) * (*ist)->phil_num);
	if (!(*ist)->control)
	{
		free(*ist);
		free((*ist)->control);
		return (error_managment(2));
	}
	pthread_mutex_init(&(*ist)->ist_mut, NULL);
	return (0);
}

long long       get_time(struct timeval init)
{
        struct timeval  timeval;

        gettimeofday(&timeval, NULL);
        return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - init.tv_sec * 1000 - init.tv_usec / 1000);
}

void	my_usleep(int mms, struct timeval init)
{
	long long int ref = get_time(init);
	while (get_time(init) - ref != mms)
		usleep(10);
}

void	*philo_rout(void *arg)
{
	philo_t	*p;
	int		i;
	int		tmp;

	p = (philo_t *) arg;
	tmp = 1;
	while (tmp) 
	{
		pthread_mutex_lock(&p->ist->ist_mut);
		tmp = p->ist->start == -1;
		pthread_mutex_unlock(&p->ist->ist_mut);		
	}

	if (p->id % 2 == 0 && p->id != p->phil_num - 1)
		my_usleep(p->tte / 10, p->ist->init);
	if (p->id == p->phil_num)
		my_usleep(p->tte / 3, p->ist->init);
	i = -1;
	while ((++i < p->nme || !p->nme) && p->ist->start != -1)
	{
		pthread_mutex_lock(&p->ist->ist_mut);
		if (p->ist->start == -1)
		{
			pthread_mutex_unlock(&p->ist->ist_mut);
			break;
		}
		pthread_mutex_unlock(&p->ist->ist_mut);
		printf("%lld ms: %d is thinking\n", get_time(p->ist->init), p->id);
		pthread_mutex_lock(p->dx_fork);
		pthread_mutex_lock(&p->ist->ist_mut);
		if (p->ist->start == -1)
		{
			pthread_mutex_unlock(&p->ist->ist_mut);
			pthread_mutex_unlock(p->dx_fork);
			break;
		}
		pthread_mutex_unlock(&p->ist->ist_mut);
		printf("%lld ms: %d has taken a fork\n", get_time(p->ist->init), p->id);
		pthread_mutex_lock(&p->sx_fork);
		pthread_mutex_lock(&p->ist->ist_mut);
		if (p->ist->start == -1)
		{
			pthread_mutex_unlock(&p->ist->ist_mut);
			pthread_mutex_unlock(&p->sx_fork);
			break;
		}
		pthread_mutex_unlock(&p->ist->ist_mut);
		printf("%lld ms: %d has taken a fork\n", get_time(p->ist->init), p->id);
		pthread_mutex_lock(&p->ist->ist_mut);
		if (p->ist->start == -1)
		{
			pthread_mutex_unlock(&p->ist->ist_mut);
			break;
		}
		pthread_mutex_unlock(&p->ist->ist_mut);
		printf("%lld ms: %d is eating\n", get_time(p->ist->init), p->id);
		my_usleep(p->tte, p->ist->init);
		p->ist->control[p->id - 1] = get_time(p->ist->init);
		if (i == p->nme - 1 && p->id == p->phil_num)
		{
			pthread_mutex_lock(&p->ist->ist_mut);
			p->ist->start = -1;
			pthread_mutex_unlock(&p->ist->ist_mut);
		}
		pthread_mutex_unlock(&p->ist->ist_mut);
		pthread_mutex_unlock(p->dx_fork);
		pthread_mutex_unlock(&p->sx_fork);
		pthread_mutex_lock(&p->ist->ist_mut);
		if (p->ist->start == -1)
		{
			pthread_mutex_unlock(&p->ist->ist_mut);
			break;
		}
		pthread_mutex_unlock(&p->ist->ist_mut);
		printf("%lld ms: %d is sleeping\n", get_time(p->ist->init), p->id);
		my_usleep(p->tts, p->ist->init);
	}
	return (0);
}

void	*control_rout(void *arg)
{
	ist_t	*ist;
	int		i;
	int		tmp;

	ist = (ist_t *) arg;
	tmp = 1;
	while (tmp)
       	{
		pthread_mutex_lock(&ist->ist_mut);
		tmp = ist->start == -1;
		pthread_mutex_unlock(&ist->ist_mut);
	}
	while (!tmp)
	{
		i = -1;
		while (++i < ist->phil_num && !tmp)
		{
			pthread_mutex_lock(&ist->ist_mut);
			if (get_time(ist->init) - ist->control[i] > ist->ttd)
			{
				ist->start = -1;
				printf("%lld ms: %d died\n", get_time(ist->init), i + 1);
				return (0);
			}	
			tmp = ist->start == -1;
			pthread_mutex_unlock(&ist->ist_mut);
		}
	}
	return (0);
}

int	philo_create(philo_t **tab, ist_t *ist, int argc, char **argv)
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
		tab[i]->phil_num = atoi(argv[1]);
		tab[i]->ttd = atoi(argv[2]);
		tab[i]->tte = atoi(argv[3]);
		tab[i]->tts = atoi(argv[4]);
		tab[i]->nme = 0;
		if (argc == 6)
			tab[i]->nme = atoi(argv[5]);
		if (pthread_create(&tab[i]->th, NULL, &philo_rout , (void *) tab[i]))
			return (error_managment(4));
	}
	while (++i < ist->phil_num)
		pthread_detach(tab[i]->th);
	i = -1;
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
	while (++i < ist->phil_num)
	{
		pthread_mutex_destroy(&tab[i]->sx_fork);
		free(tab[i]);
	}
	free(tab);
	pthread_mutex_destroy(&ist->ist_mut);
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
	//if (error_code == 7)
	//	write(2, "Error(7): error in mutex destruction\n", 38);
	return (error_code);
}
   
int main(int argc, char **argv)
{
	ist_t		*ist;
	philo_t		**tab;
	pthread_t	control_th;
	int		i;
	int		err;

	if (argc != 6 && argc != 5)
		return (error_managment(1));
	err = ist_init(&ist, argv);
	if (err)
		return (err);
	tab = (philo_t **) malloc(sizeof(philo_t *) * ist->phil_num);
	if (!tab)
		return(error_managment(2));
	err = philo_create(tab, ist, argc, argv);
	if (err)
		return (err);

	if (pthread_create(&control_th, NULL, &control_rout, (void *) ist))
		return (error_managment(4));

	
	gettimeofday(&ist->init, NULL);
	ist->start = get_time(ist->init);
	i = -1;
	while (++i < ist->phil_num)
		ist->control[i] = ist->start;


	if (pthread_join(control_th, NULL))
		return (error_managment(6));
	free_all(ist, tab);
}
