/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:24:01 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/31 11:56:54 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

//√(a^2 + b^2)
int	my_abs(t_complex complex)
{
	return (sqrt(pow(complex.real, 2) + pow(complex.imaginary, 2)));
}

// z = a + bi
// z^2 = (a + bi)^2 = (a^2 -b^2) + (2ab)i
t_complex	proc_fractol(t_complex prev_z, t_complex c)
{
	t_complex	next_z;

	next_z.real = pow(prev_z.real, 2) - pow(prev_z.imaginary, 2);
	next_z.imaginary = 2 * prev_z.real * prev_z.imaginary;
	next_z.real = next_z.real + c.real;
	next_z.imaginary = next_z.imaginary + c.imaginary;
	return (next_z);
}

int	calc_burning_ship(t_fract *fract)
{
	t_complex	z;
	int			i;

	z = complex_init(0.0, 0.0);
	i = 0;
	while (i < MAX_REPEAT)
	{
		if (my_abs(z) > 2.0)
			return (i);
		z = complex_init(fabs(z.real), fabs(z.imaginary));
		z = proc_fractol(z, fract->coordinate);
		i++;
	}
	return (i);
}

int	calc_mandelbrot_set(t_fract *fract)
{
	t_complex	z;
	int			i;

	z = complex_init(0.0, 0.0);
	i = 0;
	while (i < MAX_REPEAT)
	{
		if (my_abs(z) > 2.0)
			return (i);
		z = proc_fractol(z, fract->coordinate);
		i++;
	}
	return (MAX_REPEAT);
}

int	calc_julia_set(t_fract *fract)
{
	t_complex	z;
	int			i;

	z = fract->coordinate;
	i = 0;
	while (i < MAX_REPEAT)
	{
		if (my_abs(z) > 2.0)
			return (i);
		z = proc_fractol(z, fract->julia_c);
		i++;
	}
	return (MAX_REPEAT);
}
