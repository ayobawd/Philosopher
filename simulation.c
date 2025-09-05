/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:39:12 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:39:12 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	check_for_die(t_philo *p)
{
	int			i;
	long long	time;

	i = -1;
	while (++i < p->share->philos)
	{
		pthread_mutex_lock(&p->share->meal_mtx);
		time = get_time() - p[i].last_meal;
		pthread_mutex_unlock(&p->share->meal_mtx);
		if (time > p[i].share->time_to_die)
		{
			if (p->share->must_eat != 0)
			{
				pthread_mutex_lock(&p->share->print);
				printf("%lld %d died \n", get_time() - p->share->starting_time,
					p[i].id);
				pthread_mutex_unlock(&p->share->print);
				pthread_mutex_lock(&p->share->mtx_died);
				p->share->died = 1;
				pthread_mutex_unlock(&p->share->mtx_died);
			}
			return (0);
		}
	}
	return (1);
}

void	start_simulation(t_philo *p)
{
	int	i;

	i = 0;
	while (p->share->philos > i)
	{
		p[i].id = i + 1;
		if (pthread_create(&p[i].thread_id, NULL, &routine, &p[i]) != 0)
		{
			printf("failed");
			return ;
		}
		usleep(100);
		i++;
	}
}
