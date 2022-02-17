/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:14:22 by ynakashi          #+#    #+#             */
/*   Updated: 2022/02/04 10:20:38 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	help_fractol(void)
{
	ft_putendl_fd(COLOR_R"Invalid argument"COLOR_OFF, STDERR_FILENO);
	ft_putendl_fd("fractol usage", STDERR_FILENO);
	ft_putendl_fd("./fractol <name>", STDERR_FILENO);
	ft_putendl_fd("for example:", STDERR_FILENO);
	ft_putendl_fd("./fractol Mandelbrot", STDERR_FILENO);
	ft_putendl_fd("./fractol Julia", STDERR_FILENO);
	ft_putendl_fd("./fractol Julia <x> <y>", STDERR_FILENO);
	ft_putendl_fd("./fractol Burning_ship", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

bool	ft_isfloat(const char *str)
{
	size_t	i;
	size_t	len;
	int		dot_sign;

	len = ft_strlen(str);
	i = 0;
	dot_sign = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) || str[i] == '.')
	{
		dot_sign += 1 * (str[i] == '.');
		if (dot_sign > 1)
			return (false);
		i++;
	}
	if (len == i)
		return (true);
	else
		return (false);
}

void	check_arguments(t_fract *fract, int argc, char const *argv[])
{
	if (argc == 1)
		help_fractol();
	else if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0 && argc == 2)
		fract->draw_target = calc_mandelbrot_set;
	else if (ft_strncmp(argv[1], "Burning_ship", 13) == 0 && argc == 2)
		fract->draw_target = calc_burning_ship;
	else if (ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		fract->draw_target = calc_julia_set;
		if (argc == 2)
			fract->julia_c = complex_init(-0.04, -0.695);
		else if (argc == 4 && ft_isfloat(argv[2]) && ft_isfloat(argv[3]))
			fract->julia_c = complex_init(ft_atof(argv[2]), ft_atof(argv[3]));
		else
			help_fractol();
	}
	else
		help_fractol();
}

int	main(int argc, char const *argv[])
{
	t_fract	fract;

	check_arguments(&fract, argc, argv);
	init_param(&fract);
	if (!init_mlx(&fract))
		destroy_mlx(&fract, EXIT_FAILURE);
	setting_hooks(&fract);
	draw_fractol(&fract);
	mlx_loop(fract.mlx);
	return (0);
}
