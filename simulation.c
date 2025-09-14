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

void	*monitor_routine(void *arg)
{
	t_philo		*philos;
	int			i;
	long long	time_since_meal;
	int			all_done;

	philos = (t_philo *)arg;
	while (check_alive(philos->rules))
	{
		i = 0;
		all_done = 1;
		while (i < philos->rules->n)
		{
			pthread_mutex_lock(&philos->rules->meal_mtx);
			time_since_meal = now_ms() - philos[i].last_meal_ms;
			pthread_mutex_unlock(&philos->rules->meal_mtx);
			if (time_since_meal > philos->rules->t_die)
			{
				set_alive(philos->rules, 0);
				pthread_mutex_lock(&philos->rules->print);
				printf("%lld %d died\n", since_start_ms(philos->rules),
					philos[i].id);
				pthread_mutex_unlock(&philos->rules->print);
				return (NULL);
			}
			if (philos->rules->eat_goal != -1 
				&& philos[i].meals_eaten < philos->rules->eat_goal)
				all_done = 0;
			i++;
		}
		if (philos->rules->eat_goal != -1 && all_done)
		{
			set_alive(philos->rules, 0);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_philo *p)
{
	int	i;

	i = 0;
	while (p->rules->n > i)
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
