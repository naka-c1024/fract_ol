/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:25:15 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/30 15:25:45 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	destroy_mlx(t_fract *fract, int exit_status)
{
	if (!fract || !fract->mlx)
		exit(EXIT_FAILURE);
	if (fract->img.img)
		mlx_destroy_image(fract->mlx, fract->img.img);
	if (fract->mlx_win)
		mlx_destroy_window(fract->mlx, fract->mlx_win);
	if (fract->mlx)
		mlx_destroy_display(fract->mlx);
	exit(exit_status);
}
