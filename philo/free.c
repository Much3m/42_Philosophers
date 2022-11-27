/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 21:37:51 by min-skim          #+#    #+#             */
/*   Updated: 2022/11/27 21:02:48 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_param *par)
{
	int				n;

	free(par->tid);
	free(par->all_philo);
	free(par->forks);
	n = par->philo_num;
	while (n--)
		pthread_mutex_destroy(&par->forks[n]);
	pthread_mutex_destroy(&(par->print));
}
