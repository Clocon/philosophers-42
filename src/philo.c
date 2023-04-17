/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:26:21 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/17 13:29:22 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_actions(int nb)
{
	if (nb < 0)
		error("Arguments can't be lower than 0", 1);
	return (nb);
}

static void	init(t_action *acts, char **argv)
{
	acts->philos = check_actions(ft_atoi(argv[0]));
	acts->to_die = check_actions(ft_atoi(argv[1]));
	acts->to_eat = check_actions(ft_atoi(argv[2]));
	acts->to_sleep = check_actions(ft_atoi(argv[3]));
}

int	main(int argc, char **argv)
{
	t_action	acts;
	
	if (argc > 0)
		init(&acts, &argv[1]);
}
