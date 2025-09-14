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
	p->rules = safe_malloc(sizeof(t_rules));
	p->rules->n = philos_num;
	p->rules->alive = 1;
	p->rules->done_count = 0;
	p->rules->t_die = ft_atoi(av[2]);
	p->rules->t_eat = ft_atoi(av[3]);
	p->rules->t_sleep = ft_atoi(av[4]);
	p->rules->start_ms = now_ms();
	if (av[5])
		p->rules->eat_goal = ft_atoi(av[5]);
	else
		p->rules->eat_goal = -1;
	while (i < philos_num)
	{
		p[i].rules = p->rules;
		i++;
	}
	return (p);
}

void	data_init(t_philo *p)
{
	int	i;

	i = 0;
	p->rules->forks = safe_malloc(sizeof(pthread_mutex_t) * p->rules->n);
	pthread_mutex_init(&p->rules->meal_mtx, NULL);
	pthread_mutex_init(&p->rules->print, NULL);
	pthread_mutex_init(&p->rules->mtx_alive, NULL);
	pthread_mutex_init(&p->rules->mtx_done, NULL);
	while (i < p->rules->n)
	{
		pthread_mutex_init(&p->rules->forks[i], NULL);
		p[i].rules = p->rules;
		p[i].left = i;
		p[i].right = (i + 1) % p->rules->n;
		p[i].last_meal_ms = now_ms();
		p[i].meals_eaten = 0;
		i++;
	}
}
