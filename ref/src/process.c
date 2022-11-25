/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:07:48 by wrickard          #+#    #+#             */
/*   Updated: 2022/11/24 21:59:22 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_cnt_of_meals(t_philo *philo)
{
	int	flag_enough;
	int	i;

	if (philo->total_nbr_of_meals != -1 \
		&& philo->total_nbr_of_meals_1 > 0)
	{
		flag_enough = 1;
		i = -1;
		while (++i < philo->nbr_philo)
			if (philo[i].total_nbr_of_meals < philo->total_nbr_of_meals_1)
				flag_enough = 0;
		if (flag_enough == 1)
		{
			i = -1;
			while (i < philo[i].nbr_philo)
			{
				philo[i].stop = 1;
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	died_philo(t_philo *philo, int i)
{
	philo->arg->dead = 1;
	pthread_mutex_lock(&philo->lock_print);
	printf("%lld %d died\n", ft_time() - philo->start_time,
		philo[i].philo_id + 1);
	i = -1;
	while (i < philo[i].nbr_philo)
	{
		philo[i].stop = 1;
		i++;
	}
}

void	*ft_galina_monitor(void *args)
{
	t_philo	*philo;
	long	time_now;
	int		i;

	philo = (t_philo *)args;
	i = 0;
	while (philo[i].stop == 0)
	{
		i = -1;
		while (++i < philo->nbr_philo)
		{
			time_now = ft_time();
			if (time_now - philo[i].time_of_last_meal > philo[i].limit_of_life)
			{
				died_philo(philo, i);
				pthread_mutex_unlock(&philo->lock_print);
				return (NULL);
			}
		}
		if (ft_cnt_of_meals(philo) || philo->stop)
			return (NULL);
	}
	return (NULL);
}

void	*ft_process(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (!philo->arg->dead)
	{
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		taking_forks(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		eating(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		sleeping(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
		thinking(philo);
		if (philo->arg->dead || philo->stop || ft_cnt_of_meals(philo))
			return (NULL);
	}
	return (NULL);
}
