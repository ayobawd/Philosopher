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
	pthread_mutex_lock(&s->rules->print);
	if (check_alive(s->rules))
		printf("%lld %d %s\n", since_start_ms(s->rules), s->id, msg);
	pthread_mutex_unlock(&s->rules->print);
}

int	take_forks(t_philo *s)
{
	if (s->id % 2 == 0)
	{
		pthread_mutex_lock(&s->rules->forks[s->right]);
		pthread_mutex_lock(&s->rules->forks[s->left]);
	}
	else
	{
		pthread_mutex_lock(&s->rules->forks[s->left]);
		pthread_mutex_lock(&s->rules->forks[s->right]);
	}
	if (!check_alive(s->rules))
	{
		drop_forks(s);
		return (0);
	}
	print_action(s, "has taken a fork");
	print_action(s, "has taken a fork");
	return (1);
}
