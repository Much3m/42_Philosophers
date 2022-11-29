#include "philosophers.h"

void	end_threads(t_param *param)
{
	int		n;

	n = param->philo_num;
	while (n)
	{
		n--;
		pthread_join(param->tid[n], NULL);
	}
}

void	free_all(t_param *par)
{
	int				i;

	i = 0;
	while (i < par->philo_num)
	{
		pthread_mutex_destroy(&par->forks[i]);
		pthread_mutex_destroy(&par->all_philo[i].eat_count);
		pthread_mutex_destroy(&par->all_philo[i].eat_time);
		i++;
	}
	pthread_mutex_destroy(&(par->print));
	pthread_mutex_destroy(&(par->dead));
	free(par->tid);
	free(par->all_philo);
	free(par->forks);
}
