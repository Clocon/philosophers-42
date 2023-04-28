/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:59:49 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/27 12:07:23 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	pol;
	int	toint;

	i = 0;
	pol = 1;
	toint = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		pol = -1;
	if (nptr[i] == '+' || pol == -1)
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		toint = toint * 10 + (nptr[i++] - 48);
	return (toint * pol);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
