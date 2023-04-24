/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:21 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/24 17:32:58 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_actions(int nb, int philos)
{
	if ((nb > 2147483647 || nb < 0) && philos == 0)
		error("Arguments can't be lower than 0\n", 1);
	else if ((nb > 2147483647 || nb < 2) && philos == 1)
		error("I need more than 1 philos! and care with MAX_INT\n", 1);
	return (nb);
}

static void	action_init(t_action *acts, char **argv, int argc)
{
	if (argc > 4)
	{
		acts->n_philo = check_actions(ft_atoi(argv[0]), 1);
		acts->to_die = check_actions(ft_atoi(argv[1]), 0);
		acts->to_eat = check_actions(ft_atoi(argv[2]), 0);
		acts->to_sleep = check_actions(ft_atoi(argv[3]), 0);
		if (argv[4])
			acts->n_eat = check_actions(ft_atoi(argv[4]), 0);
		else
			acts->n_eat = -1;
		acts->is_dead = 0;
	}
	else
	{
		error(ERR_PARAM, 0);
		error(ERR_PARAM2, 1);
	}
}

void	fork_generator(t_action *acts)
{
	int	i;

	acts->forks = malloc(sizeof(pthread_mutex_t) * acts->n_philo);
	if (!acts->forks)
		error("Forks memory allocated failed\n", 1);
	i = -1;
	while (++i < acts->n_philo)
	{
		if (pthread_mutex_init(&acts->forks[i], 0))
		{
			total_free(acts);
			error("Fail to try generate fork\n", 1);
		}
	}
}

void	philos_init(t_action *acts)
{
	int	i;

	acts->philo = malloc(sizeof(t_philo) * acts->n_philo);
	if (!acts->philo)
		error("Philos memory allocated failed\n", 1);
	i = -1;
	while (++i < acts->n_philo)
	{
		acts->philo[i].act = acts;
		acts->philo[i].last_dinner = 0;
		acts->philo[i].t_seaten = 0;
		if (pthread_create(&acts->philo[i].philo, 0, thread_init,
				&acts->philo[i]))
			error("Fail creating philo\n", 1);
		acts->philo[i].id = i + 1;
		if (pthread_create(&acts->thread, 0, go_die, acts))
			error("Fail creating philo\n", 1);
	}
}

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	atexit(leaks);
	t_action	acts;	

	if (argc >6 || argc < 5)
		error("Invalid number of arguments", 1);
	action_init(&acts, &argv[1], argc);
	acts.time_start = timer();
	ft_printf("TIME = %d\n", acts.time_start);
	if (pthread_mutex_init(&acts.init, 0))
		error("Creating mutex failed\n", 1);
	fork_generator(&acts);
	philos_init(&acts);
	pthread_join(acts.thread, 0);
	exit(0);
}
