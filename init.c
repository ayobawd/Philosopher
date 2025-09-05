/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:38:35 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:38:35 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

t_philo	*philo(t_philo *p, char **av)
{
	int	philos_num;
	int	i;

	i = 0;
	philos_num = ft_atoi(av[1]);
	p = safe_malloc(sizeof(t_philo) * philos_num);
	p->share = safe_malloc(sizeof(t_share));
	p->share->philos = philos_num;
	p->share->died = 0;
	p->share->time_to_die = ft_atoi(av[2]);
	p->share->time_to_eat = ft_atoi(av[3]);
	p->share->time_to_sleep = ft_atoi(av[4]);
	p->share->starting_time = get_time();
	if (av[5])
		p->share->must_eat = ft_atoi(av[5]);
	else
		p->share->must_eat = -1;
	while (i < philos_num)
	{
		p[i].share = p->share;
		i++;
	}
	return (p);
}

void	data_init(t_philo *p)
{
	int	i;

	i = 0;
	p->share->forks = safe_malloc(sizeof(pthread_mutex_t) * p->share->philos);
	pthread_mutex_init(&p->share->meal_mtx, NULL);
	pthread_mutex_init(&p->share->print, NULL);
	pthread_mutex_init(&p->share->mtx_died, NULL);
	while (i < p->share->philos)
	{
		pthread_mutex_init(&p->share->forks[i], NULL);
		p[i].share = p->share;
		p[i].left_fork = i;
		p[i].right_fork = (i + 1) % p->share->philos;
		p[i].last_meal = get_time();
		i++;
	}
}
