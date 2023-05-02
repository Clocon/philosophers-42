/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_dead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:08:05 by lumorale          #+#    #+#             */
/*   Updated: 2023/05/02 11:32:39 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_dead(t_action *acts, int i)
{
	pthread_mutex_lock(&acts->init);
	if (timer_dif(acts) - acts->philo[i].last_dinner > acts->to_die)
	{
		acts->is_dead = 1;
		printf("%dms for %d to die\n", timer_dif(acts), acts->philo[i].id);
	}
	else
		pthread_mutex_unlock(&acts->init);
}

static int	check_eat(t_action *acts)
{
	int	i;

	i = -1;
	while (++i < acts->n_philo)
	{
		pthread_mutex_lock(&acts->init);
		if (acts->philo[i].eat_counter < acts->n_eat)
			return (pthread_mutex_unlock(&acts->init), 0);
		pthread_mutex_unlock(&acts->init);
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
			pthread_mutex_lock(&acts->init);
			acts->is_dead = 1;
			printf("All philos ate %d times\n", acts->n_eat);
			break ;
		}
	}
	return (0);
}
