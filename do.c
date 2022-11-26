/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:03:29 by min-skim          #+#    #+#             */
/*   Updated: 2022/11/26 08:45:41 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_fork_2(t_philo *philo)
{
    pthread_mutex_lock(philo->l_f);
	pthread_mutex_lock(philo->r_f);
	pthread_mutex_lock(&philo->print);
	if (philo->stop_flag != 1)
	{
		printf("%lld %d has taken a fork\n",ft_time() - philo->start_time, philo->philo_id + 1);
		printf("%lld %d has taken a fork\n",ft_time() - philo->start_time, philo->philo_id + 1);
	}
	pthread_mutex_unlock(&philo->print);
	eating(philo);
}

void	take_fork(t_philo *philo)
{
	if ((philo->philo_id) % 2 == 0)
	{
		pthread_mutex_lock(philo->l_f);
		pthread_mutex_lock(philo->r_f);
		pthread_mutex_lock(&philo->print);
		if (philo->stop_flag != 1)
		{
			printf("%lld %d has taken a fork\n",ft_time() - philo->start_time, philo->philo_id + 1);
			printf("%lld %d has taken a fork\n",ft_time() - philo->start_time, philo->philo_id + 1);
		}
		pthread_mutex_unlock(&philo->print);
		eating(philo);
	}
	else
		take_fork_2(philo);
}

void	eating(t_philo *philo)
{
	if (philo->stop_flag != 1)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lld %d is eating\n",ft_time() - philo->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->print);
		philo->total_count_eat += 1;
		philo->last_eat_time = ft_time();
		ft_usleep(philo->time_to_eat);
	}
	pthread_mutex_unlock(philo->l_f);
	pthread_mutex_unlock(philo->r_f);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->print);
	printf("%lld %d is sleeping\n",ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->print);
	ft_usleep(philo->time_to_sleep);
	usleep(100);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->print);
	printf("%lld %d is thinking\n",ft_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->print);
}
