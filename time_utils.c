/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/01/27 00:00:00 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	since_start_ms(t_rules *r)
{
	return (now_ms() - r->start_ms);
}

void	smart_usleep(long long ms, t_rules *r)
{
	long long	start;
	long long	elapsed;

	start = now_ms();
	while (check_alive(r))
	{
		elapsed = now_ms() - start;
		if (elapsed >= ms)
			break ;
		usleep(200);
	}
}

int	check_alive(t_rules *rules)
{
	int	alive;

	pthread_mutex_lock(&rules->mtx_alive);
	alive = rules->alive;
	pthread_mutex_unlock(&rules->mtx_alive);
	return (alive);
}

void	set_alive(t_rules *rules, int value)
{
	pthread_mutex_lock(&rules->mtx_alive);
	rules->alive = value;
	pthread_mutex_unlock(&rules->mtx_alive);
}