#include "philosophers.h"

int	init_param(t_param *par, int ac, char **av)
{
	par->philo_num = ft_atoi(av[1]);
	par->time_to_die = ft_atoi(av[2]);
	par->time_to_eat = ft_atoi(av[3]);
	par->time_to_sleep = ft_atoi(av[4]);
	par->dead_flag = 0;
	par->nbr_of_meals = -1;
	if (ac == 6)
		par->nbr_of_meals = ft_atoi(av[5]);
	if (par->nbr_of_meals == 0)
		return (ft_error("0 all philo eat 0 time"));
	if (par->philo_num == 1)
	{
		printf("%d %d has taken a fork\n", 0, 1);
		ft_usleep(par->time_to_die);
		printf("%d %d died\n", par->time_to_die, 1);
		return (1);
	}
	return (0);
}

int	init_philosophers(t_param *par)
{
	int				i;
	t_philo			*philos;

	i = -1;
	philos = malloc(sizeof(t_philo) * par->philo_num);
	if (!philos)
		return (ft_error("Malloc philos Failed"));
	par->start_time = ft_time();
	while (++i < par->philo_num)
	{
		philos[i].philo_id = i;
		philos[i].philo_num = par->philo_num;
		philos[i].total_count_eat = 0;
		philos[i].total_count_eat_2 = par->nbr_of_meals;
		philos[i].time_to_eat = par->time_to_eat;
		philos[i].time_to_sleep = par->time_to_sleep;
		philos[i].last_eat_time = par->start_time;
		philos[i].start_time = par->start_time;
		philos[i].limit_lifetime = par->time_to_die;
		philos[i].l_f = &par->forks[philos[i].philo_id];
		philos[i].r_f = &par->forks[(philos[i].philo_id + 1) % par->philo_num];
		philos[i].param = par;
	}
	par->all_philo = philos;
	return (0);
}

int	init_mutex(t_param *par)
{
	int				size;
	pthread_mutex_t	*mutex;

	size = par->philo_num;
	mutex = malloc(sizeof(pthread_mutex_t) * size);
	if (!mutex)
		return (ft_error("Error : Malloc Mutex Failed"));
	while (size--)
		pthread_mutex_init(&mutex[size], NULL);
	pthread_mutex_init(&par->print, NULL);
	pthread_mutex_init(&par->dead, NULL);
	par->forks = mutex;
	return (0);
}

int	init_mutex2(t_philo *philos)
{
	int				i;

	i = 0;
	while (i < philos->philo_num)
	{
		pthread_mutex_init(&(philos[i].eat_count), NULL);
		pthread_mutex_init(&(philos[i].eat_time), NULL);
		i++;
	}
	return (0);
}

int	init_thread(t_param *par)
{
	int			i;
	pthread_t	*threads;
	pthread_t	s_tid;

	i = 0;
	threads = malloc(sizeof(pthread_t) * par->philo_num);
	if (!threads)
		return (ft_error("Error : Malloc Thread Failed"));
	while (i < par->philo_num)
	{
		pthread_create(&threads[i], NULL, philo_routine, \
		(void *)&par->all_philo[i]);
		i++;
	}
	pthread_create(&s_tid, NULL, monitoring, (void *)par->all_philo);
	pthread_join(s_tid, NULL);
	par->tid = threads;
	return (0);
}
