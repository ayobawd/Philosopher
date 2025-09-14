/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:39:00 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:39:00 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

void	drop_forks(t_philo *s)
{
	pthread_mutex_unlock(&s->rules->forks[s->left]);
	pthread_mutex_unlock(&s->rules->forks[s->right]);
}

void	*routine(void *arg)
{
	t_philo	*s;

	s = (t_philo *)arg;
	while (check_alive(s->rules))
	{
		print_action(s, "is thinking");
		if (!take_forks(s))
			return (NULL);
		pthread_mutex_lock(&s->rules->meal_mtx);
		s->last_meal_ms = now_ms();
		pthread_mutex_unlock(&s->rules->meal_mtx);
		print_action(s, "is eating");
		smart_usleep(s->rules->t_eat, s->rules);
		s->meals_eaten++;
		drop_forks(s);
		if (!check_alive(s->rules))
			return (NULL);
		print_action(s, "is sleeping");
		smart_usleep(s->rules->t_sleep, s->rules);
	}
	return (NULL);
}
