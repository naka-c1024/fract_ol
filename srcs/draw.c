/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:24:06 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/31 08:23:48 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	get_color(int repeat)
{
	if (repeat == MAX_REPEAT)
		return (0x00FF0000);
	else if (repeat % 2 == 0)
		return (0x0000FF00);
	else if (repeat % 2 != 0)
		return (0x000000FF);
	else
		return (0);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_fractol(t_fract *fract)
{
	int			x;
	int			y;
	int			color;
	t_complex	pixel;

	pixel.real = (fract->max.real - fract->min.real) / (fract->width - 1);
	pixel.imaginary = (fract->max.imaginary - fract->min.imaginary)
		/ (fract->height - 1);
	y = 0;
	while (y < fract->height)
	{
		fract->coordinate.imaginary = fract->min.imaginary
			+ y * pixel.imaginary;
		x = 0;
		while (x < fract->width)
		{
			fract->coordinate.real = fract->min.real + x * pixel.real;
			color = get_color(fract->draw_target(fract));
			my_mlx_pixel_put(&(fract->img), x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fract->mlx, fract->mlx_win, fract->img.img, 0, 0);
}
