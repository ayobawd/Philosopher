/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:38:25 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/14 14:58:35 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *p)
{
	int		i;
	t_rules	*r;

	r = p->rules;
	if (!p || !r)
		return ;
	pthread_mutex_destroy(&r->print);
	pthread_mutex_destroy(&r->meal_mtx);
	pthread_mutex_destroy(&r->mtx_alive);
	pthread_mutex_destroy(&r->mtx_done);
	if (r->forks)
	{
		i = 0;
		while (i < r->n)
		{
			pthread_mutex_destroy(&r->forks[i]);
			i++;
		}
		free(r->forks);
	}
	free(r);
	free(p);
}

void	*safe_malloc(size_t size)
{
	void	*a;

	a = malloc(size);
	if (a == NULL)
	{
		error_exit("Error: malloc failed\n");
		return (0);
	}
	return (a);
}

void	error_exit(char *error)
{
	printf("%s\n", error);
	return ;
}
