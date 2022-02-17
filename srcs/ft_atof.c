/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 13:22:14 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/30 17:27:03 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	read_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

double	ft_atof(const char *nptr)
{
	size_t	i;
	double	ans;
	int		sign;
	double	div;

	i = 0;
	ans = 0;
	while (('\t' <= nptr[i] && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
		sign = read_sign(nptr[i++]);
	while (ft_isdigit(nptr[i]))
		ans = ans * 10.0 + (nptr[i++] - '0');
	if (nptr[i] == '.')
		i++;
	div = 1;
	while (ft_isdigit(nptr[i]))
	{
		ans = ans * 10.0 + (nptr[i++] - '0');
		div *= 10.0;
	}
	return (sign * ans / div);
}
