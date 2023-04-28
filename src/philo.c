/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:21 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/28 17:02:21 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_actions(char *str)
{
	int	i;
	int	nb;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			error("It's not a numeric character\n", 1);
	}
	nb = ft_atoi(str);
	if (nb > 2147483647 || nb < 0)
		error("Arguments can't be lower than 0 and care with MAX_INT\n", 1);
	return (nb);
}

static void	action_init(t_action *acts, char **argv, int argc)
{
	if (argc > 4)
	{
		acts->n_philo = check_actions(argv[0]);
		acts->to_die = check_actions(argv[1]);
		acts->to_eat = check_actions(argv[2]);
		acts->to_sleep = check_actions(argv[3]);
		if (argv[4])
			acts->n_eat = check_actions(argv[4]);
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
	if (pthread_create(&acts->thread, 0, go_die, acts))
		error("Fail creating thread\n", 1);
	while (++i < acts->n_philo)
	{
		acts->philo[i].act = acts;
		acts->philo[i].last_dinner = 0;
		acts->philo[i].eat_counter = 0;
		acts->philo[i].id = i + 1;
		acts->philo[i].i_eat = 0;
		if (pthread_create(&acts->philo[i].philo, 0, thread_init,
				&acts->philo[i]))
			error("Fail creating philo\n", 1);
	}
}

int	main(int argc, char **argv)
{
	t_action	acts;

	if (argc > 6 || argc < 5)
		error("Invalid number of arguments", 1);
	action_init(&acts, &argv[1], argc);
	acts.time_start = timer();
	if (pthread_mutex_init(&acts.init, 0))
		error("Creating mutex failed\n", 1);
	fork_generator(&acts);
	philos_init(&acts);
	pthread_join(acts.thread, 0);
	exit(0);
}
