/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:38:42 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/14 14:59:12 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		*p;
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	p = NULL;
	if (ac != 5 && ac != 6)
		return (error_exit("Error: wrong number of arguments"), 0);
	if (!check(av, ac) || !parsing(av))
		return (0);
	p = philo(p, av);
	data_init(p);
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, p) != 0)
		return (error_exit("Failed to create monitor thread"), 0);
	start_simulation(p);
	pthread_join(monitor_thread, NULL);
	while (i < p->rules->n)
	{
		pthread_join(p[i].thread_id, NULL);
		i++;
	}
	return (free_all(p), 0);
}
