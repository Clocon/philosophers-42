/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:51:53 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/28 17:01:43 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_PARAM "Usage: ./philo number_philos time_die tiem_eat time_sleep"
# define ERR_PARAM2 " and number of times must eat each philo \n"

typedef struct s_philo
{
	void			*act;
	pthread_t		philo;
	int				id;
	int				l_fork;
	int				r_fork;
	int				last_dinner;
	int				eat_counter;
	int				i_eat;
}	t_philo;

typedef struct s_action
{
	int				n_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				n_eat;
	int				time_start;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	init;
	t_philo			*philo;
	pthread_t		thread;
}	t_action;

/*Functions for freerror.c*/
void	error(char *str, int to_exit);
void	total_free(t_action *acts);
void	msg(t_action *acts, char *str, int time, int id);

/*Functions for timer.c*/
int		timer(void);
int		timer_dif(t_action *acts);
void	to_sleep(t_action *acts, int time);

/*Functions for threads.c*/
void	*thread_init(void *ph);
void	*go_die(void *ph);

/*Functions for threads.c*/
int		ft_atoi(char *nptr);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);

#endif
