/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:27:24 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/24 17:41:33 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	msg(t_action *acts, char *str, int time, int id)
{
	pthread_mutex_lock(&acts->init);
	printf("%dms %d %s\n", time, id, str);
	pthread_mutex_unlock(&acts->init);
}

void	error(char *str, int to_exit)
{
	ft_putstr_fd(str, 2);
	if (to_exit == 1)
		exit(1);
}

void	total_free(t_action *acts)
{
	int	i;

	i = -1;
	while (++i < acts->n_philo)
		pthread_mutex_destroy(&acts->forks[i]);
	pthread_mutex_destroy(&acts->init);
	free(acts->forks);
	if (acts->philo)
		free(&acts->philo);
}

