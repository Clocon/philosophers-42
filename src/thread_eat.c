/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:55:42 by lumorale          #+#    #+#             */
/*   Updated: 2023/05/02 11:38:14 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	go_eat_r(t_philo *philo, t_action *acts)
{
	pthread_mutex_lock(&acts->forks[philo->l_fork]);
	msg(acts, "has taken a fork", timer_dif(acts), philo->id);
	pthread_mutex_lock(&acts->forks[philo->r_fork]);
	msg(acts, "has taken a fork", timer_dif(acts), philo->id);
	if (!acts->is_dead)
	{
		pthread_mutex_lock(&acts->init);
		philo->last_dinner = timer_dif(acts);
		philo->eat_counter++;
		pthread_mutex_unlock(&acts->init);
		msg(acts, "is eating", philo->last_dinner, philo->id);
	}
	to_sleep(acts, acts->to_eat);
	pthread_mutex_unlock(&acts->forks[philo->l_fork]);
	pthread_mutex_unlock(&acts->forks[philo->r_fork]);
}

static void	go_eat_l(t_philo *philo, t_action *acts)
{
	pthread_mutex_lock(&acts->forks[philo->r_fork]);
	msg(acts, "has taken a fork", timer_dif(acts), philo->id);
	pthread_mutex_lock(&acts->forks[philo->l_fork]);
	msg(acts, "has taken a fork", timer_dif(acts), philo->id);
	if (!acts->is_dead)
	{
		pthread_mutex_lock(&acts->init);
		philo->last_dinner = timer_dif(acts);
		philo->eat_counter++;
		pthread_mutex_unlock(&acts->init);
		msg(acts, "is eating", philo->last_dinner, philo->id);
	}
	to_sleep(acts, acts->to_eat);
	pthread_mutex_unlock(&acts->forks[philo->r_fork]);
	pthread_mutex_unlock(&acts->forks[philo->l_fork]);
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
		if (philo->id % 2 == 0)
			go_eat_r(philo, acts);
		if (philo->id % 2 == 1)
			go_eat_l(philo, acts);
		msg(acts, "is sleeping", timer_dif(acts), philo->id);
		usleep(acts->to_sleep * 1000);
		msg(acts, "is thinking", timer_dif(acts), philo->id);
	}
	return (0);
}
