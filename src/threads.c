/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:55:42 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/21 17:47:14 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	go_eat(t_philo *philo, t_action *acts)
{
	pthread_mutex_lock(&acts->forks[philo->l_fork]);
	msg(acts, "takes a fork", timer_dif(acts), philo->id);
	pthread_mutex_lock(&acts->forks[philo->r_fork]);
	msg(acts, "takes a fork", timer_dif(acts), philo->id);
	philo->last_dinner = timer_dif(acts);
	//printf("ULTIMA CENA!! = %d\n", philo->last_dinner);
	msg(acts, "is eating", timer_dif(acts), philo->id);
	philo->t_seaten++;
	to_sleep(acts, acts->to_eat);
	pthread_mutex_unlock(&acts->forks[philo->l_fork]);
	pthread_mutex_unlock(&acts->forks[philo->r_fork]);
}

static void	check_dead(t_action *acts, int i)
{
	if (timer_dif(acts) - acts->philo[i].last_dinner > acts->to_die)
	{
		acts->is_dead = 1;
		printf("%dms for %d, to die\n", timer_dif(acts), acts->philo[i].id);
		return ;
	}
	if (acts->philo[i].t_seaten >= acts->n_eat)
		acts->times_eaten++;
}

void	*go_die(void *ac)
{
	t_action	*acts;
	int			i;

	acts = ac;
	while (!acts->is_dead)
	{
		i = -1;
		acts->times_eaten = 0;
		while (++i < acts->n_philo && !acts->is_dead)
			check_dead(acts, i);
		if (acts->n_eat > -1 && acts->times_eaten == acts->n_philo)
		{
			acts->is_dead = 1;
			printf("All philos ate %d times\n", acts->n_eat);
		}
	}
	i = -1;
	while (++i < acts->n_philo)
		pthread_join(acts->philo[i].philo, 0);
	return (0);
}

void	*thread_init(void *ph)
{
	t_philo		*philo;
	t_action	*acts;

	philo = ph;
	acts = philo->act;

	if (philo->r_fork == acts->n_philo)
		philo->r_fork = 0;
	else
		philo->r_fork = philo->id;
	if (philo->id - 1 < 0)
		philo->l_fork = acts->n_philo;
	else
		philo->l_fork = philo->id - 1;

	if (philo->id % 2 == 0)
		usleep(250);
	while (!acts->is_dead)
	{
		go_eat(philo, acts);
		msg(acts, "is sleeping", timer_dif(acts), philo->id);
		msg(acts, "is thinking", timer_dif(acts), philo->id);

	}
	return (0);
}