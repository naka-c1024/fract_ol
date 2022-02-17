/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:24:10 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/31 08:25:17 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_complex	complex_init(double real, double imaginary)
{
	t_complex	complex;

	complex.real = real;
	complex.imaginary = imaginary;
	return (complex);
}

void	init_param(t_fract *fract)
{
	fract->max = complex_init(2.0, 2.0);
	fract->min = complex_init(-2.0, -2.0);
}

bool	init_mlx(t_fract *fract)
{
	fract->mlx = NULL;
	fract->mlx_win = NULL;
	fract->img.img = NULL;
	fract->mlx = mlx_init();
	if (!fract->mlx)
		return (false);
	mlx_get_screen_size(fract->mlx, &fract->width, &fract->height);
	fract->width = fmin(fract->width, WIDTH);
	fract->height = fmin(fract->height, HEIGHT);
	fract->mlx_win = mlx_new_window(
			fract->mlx, fract->width, fract->height, "fractol");
	if (!fract->mlx_win)
		return (false);
	fract->img.img = mlx_new_image(fract->mlx, fract->width, fract->height);
	if (!fract->img.img)
		return (false);
	fract->img.addr = mlx_get_data_addr(fract->img.img,
			&(fract->img.bits_per_pixel),
			&(fract->img.line_length), &(fract->img.endian));
	if (!fract->img.addr)
		return (false);
	return (true);
}
