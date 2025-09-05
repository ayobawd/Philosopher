/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:38:50 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:38:50 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"

int	check(char **av, int ac)
{
	int	j;
	int	i;

	j = 1;
	if (ft_atoi(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		sleeper(ft_atoi(av[2]));
		printf("%d 1 died\n", (ft_atoi(av[2])));
		return (0);
	}
	while (ac > j)
	{
		i = 0;
		while (av[j][i])
		{
			if (!ft_isdigit(av[j][i]))
				return (error_exit("Error : Non-numeric"), 0);
			i++;
		}
		if (av[j][0] == '\0')
			return (error_exit("Error: empty argument"), 0);
		j++;
	}
	return (1);
}

int	parsing(char **av)
{
	int	must_eat;

	must_eat = 0;
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (error_exit("Error: Values must be > 0"), 0);
	if (av[5])
	{
		must_eat = ft_atoi(av[5]);
		if (must_eat <= 0)
			return (error_exit("Error: (must_eat) must be > 0"), 0);
	}
	return (1);
}
