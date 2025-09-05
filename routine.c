/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:39:04 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:39:04 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	print_action(t_philo *s, char *msg)
{
	pthread_mutex_lock(&s->share->print);
	printf("%lld %d %s\n",
		get_time() - s->share->starting_time, s->id, msg);
	pthread_mutex_unlock(&s->share->print);
}

int	check_death(t_philo *s)
{
	int	d;

	pthread_mutex_lock(&s->share->mtx_died);
	d = s->share->died;
	pthread_mutex_unlock(&s->share->mtx_died);
	return (d);
}

void	think(t_philo *s)
{
	if (!check_death(s))
		print_action(s, "is thinking");
}

int	take_forks(t_philo *s)
{
	if (s->id % 2 == 0)
	{
		pthread_mutex_lock(&s->share->forks[s->right_fork]);
		pthread_mutex_lock(&s->share->forks[s->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&s->share->forks[s->left_fork]);
		pthread_mutex_lock(&s->share->forks[s->right_fork]);
	}
	if (check_death(s))
	{
		drop_forks(s);
		return (0);
	}
	print_action(s, "has taken a fork");
	print_action(s, "has taken a fork");
	return (1);
}

int	eat(t_philo *s, int *meals)
{
	long long	now;

	now = get_time();
	pthread_mutex_lock(&s->share->meal_mtx);
	s->last_meal = now;
	pthread_mutex_unlock(&s->share->meal_mtx);
	print_action(s, "is eating");
	sleeper(s->share->time_to_eat);
	pthread_mutex_lock(&s->share->meal_mtx);
	(*meals)--;
	pthread_mutex_unlock(&s->share->meal_mtx);
	if (check_death(s))
	{
		drop_forks(s);
		return (0);
	}
	return (1);
}
