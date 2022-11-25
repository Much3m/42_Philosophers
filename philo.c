/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:13:06 by min-skim          #+#    #+#             */
/*   Updated: 2022/11/25 21:45:46 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	count_meals(t_philo *philo)
{
	int		flag;
	int		i;

	if (philo->total_count_eat_2 != -1)
	{
		flag = 1;
		i = -1;
		while (++i < philo->philo_num)
			if(philo[i].total_count_eat < philo->total_count_eat_2)
				flag = 0;
		if (flag == 1)
		{
			i = 0;
			while (i < philo->philo_num)
			{
				philo[i].stop_flag = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	dead(t_philo *philo, int i)
{
	philo->param->dead_flag = 1;
	pthread_mutex_lock(&philo->print);
	printf("%lld %d died\n", ft_time() - philo->start_time, philo[i].philo_id + 1);
	i = 0;
	while (i < philo[i].philo_num)
	{
		philo[i].stop_flag = 1;
		i++;
	}
}

void	*monitoring(void *a)
{
	t_philo 	*philo;
	long long	current;
	int			i;

	philo = (t_philo *)a;
	i = 0;
	while (philo->stop_flag != 1)
	{
		i = -1;
		while (++i < philo->philo_num)
		{
			current = ft_time();
			if (current - philo[i].last_eat_time > philo[i].limit_lifetime)
			{
				dead(philo, i);
				pthread_mutex_unlock(&philo->print);
				return (NULL);
			}
		}
		if (count_meals(philo) || philo->stop_flag)
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	if (philo->philo_id % 2 != 0)
		ft_usleep(philo->time_to_eat / 3);
	while (!philo->param->dead_flag)
	{
		if (philo->param->dead_flag || philo->stop_flag || count_meals(philo))
			return (NULL);
		take_fork(philo);
		if (philo->param->dead_flag || philo->stop_flag || count_meals(philo))
			return (NULL);
		sleeping(philo);
		if (philo->param->dead_flag || philo->stop_flag || count_meals(philo))
			return (NULL);
		thinking(philo);
		if (philo->param->dead_flag || philo->stop_flag || count_meals(philo))
			return (NULL);
	}
	return (NULL);
}
