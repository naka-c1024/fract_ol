/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:38:21 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/31 09:43:46 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	move(int key_code, t_fract *fract)
{
	t_complex	dist;

	dist.real = (fract->max.real - fract->min.real) / 10;
	dist.imaginary = (fract->max.imaginary - fract->min.imaginary) / 10;
	if (key_code == LEFT_ARROW)
	{
		fract->max.real += -dist.real;
		fract->min.real += -dist.real;
	}
	if (key_code == RIGHT_ARROW)
	{
		fract->max.real += dist.real;
		fract->min.real += dist.real;
	}
	if (key_code == UP_ARROW)
	{
		fract->max.imaginary += -dist.imaginary;
		fract->min.imaginary += -dist.imaginary;
	}
	if (key_code == DOWN_ARROW)
	{
		fract->max.imaginary += (key_code == DOWN_ARROW) * dist.imaginary;
		fract->min.imaginary += (key_code == DOWN_ARROW) * dist.imaginary;
	}
	draw_fractol(fract);
}

int	deal_key(int key_code, t_fract *fract)
{
	if (key_code == KEY_ESC)
		destroy_mlx(fract, EXIT_SUCCESS);
	if (key_code == LEFT_ARROW)
		move(key_code, fract);
	if (key_code == UP_ARROW)
		move(key_code, fract);
	if (key_code == RIGHT_ARROW)
		move(key_code, fract);
	if (key_code == DOWN_ARROW)
		move(key_code, fract);
	if (key_code == D)
		zoom(key_code, fract);
	if (key_code == U)
		zoom(key_code, fract);
	return (0);
}

void	zoom(int key_code, t_fract *fract)
{
	t_complex	dist;

	dist.real = (fract->max.real - fract->min.real) / 50;
	dist.imaginary = (fract->max.imaginary - fract->min.imaginary) / 50;
	if (key_code == D || key_code == SCROLL_DOWN)
	{
		fract->max.real += dist.real;
		fract->min.real += -dist.real;
		fract->max.imaginary += dist.imaginary;
		fract->min.imaginary += -dist.imaginary;
	}
	else if (key_code == U || key_code == SCROLL_UP)
	{
		fract->max.real += -dist.real;
		fract->min.real += dist.real;
		fract->max.imaginary += -dist.imaginary;
		fract->min.imaginary += dist.imaginary;
	}
	draw_fractol(fract);
}

int	zoom_deal_key(int key_code, int i, int j, t_fract *fract)
{
	i = (double)i;
	j = (double)j;
	if (key_code == SCROLL_UP)
		zoom(key_code, fract);
	else if (key_code == SCROLL_DOWN)
		zoom(key_code, fract);
	return (0);
}

void	setting_hooks(t_fract *fract)
{
	mlx_hook(fract->mlx_win, KEY_PRESS, KEY_PRESS_MASK, deal_key, fract);
	mlx_mouse_hook(fract->mlx_win, zoom_deal_key, fract);
}
