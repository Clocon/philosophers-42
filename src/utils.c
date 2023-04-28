/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumorale <lumorale@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:59:49 by lumorale          #+#    #+#             */
/*   Updated: 2023/04/28 17:48:24 by lumorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *nptr)
{
	int		i;
	int		pol;
	long	toint;

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
	if (toint > 2147483647)
		return (-1);
	toint *= pol;
	return ((int)toint);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
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
