/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:15:11 by min-skim          #+#    #+#             */
/*   Updated: 2022/11/25 00:16:52 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argv(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1)
		return (1);
	if (ft_atoi(argv[2]) < 0)
		return (1);
	if (ft_atoi(argv[3]) < 0)
		return (1);
	if (ft_atoi(argv[4]) < 0)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 0)
			return (1);
	return (0);
}

int validate(int ac, char **av)
{
    int             i;

    if (ac < 5 || ac > 6)
       return (ft_error("Error : Check Number of Argumets")); 
    i = 1;
    while (av[i])
    {
        if (!is_digit(av[i]))
            return (ft_error("Error : Invalid Argumet"));
        i++;
    }
    if (check_argv(ac, av))
        return (ft_error("Error : Check the Value of Argumets"));;
    return (0);
}

int main(int ac, char **av)
{
    t_param     param;

    if (validate(ac, av))
        return (1);
    if (init_param(&param, ac, av))
        return (1);
    init_mutex(&param);
    init_philosophers(&param);
    init_thread(&param);
    end_threads(&param);
    free_all(&param);
    return (0);
}
