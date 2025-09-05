/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-awa <ayal-awa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:38:55 by ayal-awa          #+#    #+#             */
/*   Updated: 2025/09/05 17:38:55 by ayal-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# define TAB '\t'
# define BACKSPACE '\b'
# define CARRIAGE '\r'
# define SPACE ' '
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h> 
# include <stdbool.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_share
{
	int			philos;
	int			time_to_die;
	int			time_to_eat;
	long long	start_eating;
	int			time_to_sleep;
	int			must_eat;
	int			died;
	long long	starting_time;
	t_mtx		print;
	t_mtx		meal_mtx;
	t_mtx		*forks;
	t_mtx		mtx_died;
}	t_share;

typedef struct s_philo
{
	int			id;
	int			meals_count;
	int			left_fork;
	int			right_fork;
	long long	last_meal;
	t_mtx		*meal_mtx;
	pthread_t	thread_id;
	t_share		*share;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		free_all(t_philo *p);
int			check(char **av, int ac);
void		*routine(void *arg);
void		*safe_malloc(size_t size);
void		error_exit(char *error);
void		start_simulation(t_philo *p);
void		sleeper(size_t milliseconds);
int			parsing(char **av);
t_philo		*philo(t_philo *p, char **av);
void		data_init(t_philo *p);
long long	get_time(void);
int			check_for_die(t_philo *p);
int			check_death(t_philo *s);
void		print_action(t_philo *s, char *msg);
void		think(t_philo *s);
int			take_forks(t_philo *s);
int			eat(t_philo *s, int *meals);
void		drop_forks(t_philo *s);
void		sleep_philo(t_philo *s);
#endif
