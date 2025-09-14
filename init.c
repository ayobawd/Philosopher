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

void	init_rules(t_rules *rules, char **av)
{
	rules->n = ft_atoi(av[1]);
	rules->alive = 1;
	rules->done_count = 0;
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	rules->start_ms = now_ms();
	if (av[5])
		rules->eat_goal = ft_atoi(av[5]);
	else
		rules->eat_goal = -1;
}

t_philo	*philo(t_philo *p, char **av)
{
	int	philos_num;
	int	i;

	i = 0;
	philos_num = ft_atoi(av[1]);
	p = safe_malloc(sizeof(t_philo) * philos_num);
	p->rules = safe_malloc(sizeof(t_rules));
	init_rules(p->rules, av);
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
