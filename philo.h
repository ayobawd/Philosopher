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

typedef struct s_rules
{
	int			n;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			eat_goal;
	long long	start_ms;
	int			alive;
	int			done_count;
	t_mtx		print;
	t_mtx		*forks;
	t_mtx		meal_mtx;
	t_mtx		mtx_alive;
	t_mtx		mtx_done;
}	t_rules;

typedef struct s_philo
{
	int			id;
	int			left;
	int			right;
	long long	last_meal_ms;
	int			meals_eaten;
	t_rules		*rules;
	pthread_t	thread_id;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		free_all(t_philo *p);
int			check(char **av, int ac);
void		*routine(void *arg);
void		*safe_malloc(size_t size);
void		error_exit(char *error);
void		start_simulation(t_philo *p);
int			parsing(char **av);
t_philo		*philo(t_philo *p, char **av);
void		data_init(t_philo *p);
long long	now_ms(void);
long long	since_start_ms(t_rules *r);
void		smart_usleep(long long ms, t_rules *r);
void		*monitor_routine(void *arg);
void		print_action(t_philo *s, char *msg);
int			take_forks(t_philo *s);
void		drop_forks(t_philo *s);
void		drop_forks(t_philo *s);
int			check_alive(t_rules *rules);
void		set_alive(t_rules *rules, int value);
int			check_philosopher_death(t_philo *philos, int i);
int			check_meal_goal(t_philo *philos);
void		init_rules(t_rules *rules, char **av);
int			handle_single_philo(char **av);
int			validate_arguments(char **av, int ac);
int			philo_eat(t_philo *s);
#endif
