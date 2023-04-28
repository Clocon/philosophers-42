/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:55:42 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/28 16:59:36 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_dead(t_action *acts, int i)
{
	if (timer_dif(acts) - acts->philo[i].last_dinner > acts->to_die)
	{
		acts->is_dead = 1;
		pthread_mutex_lock(&acts->init);
		printf("%dms for %d to die\n", timer_dif(acts), acts->philo[i].id);
	}
}

static int	check_eat(t_action *acts)
{
	int	i;

	i = -1;
	while (++i < acts->n_philo)
	{
		if (acts->philo[i].eat_counter < acts->n_eat)
			return (0);
	}
	return (1);
}

void	*go_die(void *ac)
{
	t_action	*acts;
	int			i;

	acts = ac;
	while (!acts->is_dead)
	{
		i = -1;
		while (++i < acts->n_philo && !acts->is_dead)
			check_dead(acts, i);
		if (!acts->is_dead && acts->n_eat > 0 && check_eat(acts))
		{
			acts->is_dead = 1;
			pthread_mutex_lock(&acts->init);
			printf("All philos ate %d times\n", acts->n_eat);
			break ;
		}
	}
	return (0);
}

static void	go_eat(t_philo *philo, t_action *acts)
{
	pthread_mutex_lock(&acts->forks[philo->l_fork]);
	msg(acts, "has taken a fork", timer_dif(acts), philo->id);
	pthread_mutex_lock(&acts->forks[philo->r_fork]);
	msg(acts, "has taken a fork", timer_dif(acts), philo->id);
	if (!acts->is_dead)
	{
		philo->last_dinner = timer_dif(acts);
		msg(acts, "is eating", philo->last_dinner, philo->id);
		philo->eat_counter++;
	}
	to_sleep(acts, acts->to_eat);
	pthread_mutex_unlock(&acts->forks[philo->l_fork]);
	pthread_mutex_unlock(&acts->forks[philo->r_fork]);
}

void	*thread_init(void *ph)
{
	t_philo		*philo;
	t_action	*acts;

	philo = ph;
	acts = philo->act;
	philo->r_fork = philo->id - 1;
	if (philo->id == acts->n_philo)
		philo->l_fork = 0;
	else
		philo->l_fork = philo->id;
	if (philo->id % 2 == 0)
		usleep(250);
	while (!acts->is_dead)
	{
		if (philo->eat_counter >= acts->n_eat && acts->n_eat > 0)
			break ;
		go_eat(philo, acts);
		msg(acts, "is sleeping", timer_dif(acts), philo->id);
		usleep(acts->to_sleep * 1000);
		msg(acts, "is thinking", timer_dif(acts), philo->id);
	}
	return (0);
}
