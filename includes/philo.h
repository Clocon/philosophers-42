/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:51:53 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/17 13:22:16 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include "../get_next_line/includes/get_next_line.h"

typedef struct s_action
{
	int	philos;
	int	to_die;
	int	to_eat;
	int	to_sleep;
}	t_action;


/*Functions for freerror.c*/
void	error(char *str, int to_exit);

#endif
