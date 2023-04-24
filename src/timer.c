/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:50:54 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/24 15:49:31 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	timer(void)
{
	struct timeval	time;
	int				ret;

	gettimeofday(&time, 0);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

int	timer_dif(t_action *acts)
{
	return (timer() - acts->time_start);
}

void	to_sleep(t_action *acts, int time)
{
	int	sleep_init;

	sleep_init = timer_dif(acts);
	while (timer_dif(acts) - sleep_init < time)
		usleep(50);
}
