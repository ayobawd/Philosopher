/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:39:16 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:39:17 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > INT_MAX)
		{
			error_exit("Error: Values must be < 2147483647");
			return (exit(1), 0);
		}
		i++;
	}
	return ((int)(result * sign));
}

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
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
