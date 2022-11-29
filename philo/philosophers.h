/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:46:18 by min-skim          #+#    #+#             */
/*   Updated: 2022/11/29 19:55:56 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				total_count_eat;
	int				total_count_eat_2;
	long long		last_eat_time;
	int				philo_num;
	int				time_to_eat;
	int				time_to_sleep;
	long long		limit_lifetime;
	long long		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	eat_count;
	pthread_mutex_t	eat_time;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	struct s_param	*param;
}				t_philo;

typedef struct s_param
{
	int				philo_num;
	int				philo_id;
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead_flag;
	int				nbr_of_meals;
	pthread_mutex_t	*forks;
	pthread_t		*tid;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	t_philo			*all_philo;
}			t_param;
/*utils*/
long long	ft_time(void);
int			ft_atoi(const char *str);
int			is_digit(char *str);
void		ft_usleep(int ms);
int			ft_error(char *s);

void		*monitoring(void *a);
void		*philo_routine(void *a);

int			init_param(t_param *par, int ac, char **av);
int			init_philosophers(t_param *par);
int			init_mutex(t_param *par);
int			init_thread(t_param *par);
int			init_mutex2(t_philo *philos);
void		end_threads(t_param *param);

void		free_all(t_param *par);

void		take_fork(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

#endif
