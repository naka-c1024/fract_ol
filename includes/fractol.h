/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:13:55 by ynakashi          #+#    #+#             */
/*   Updated: 2022/01/31 13:25:08 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# include <unistd.h> // close read write
# include <stdlib.h> // malloc free exit
# include <math.h> // math function
# include <stdbool.h> // true false

# define WIDTH		100 // 描画の横幅
# define HEIGHT		100 // 描画の縦幅
# define MAX_REPEAT	200 // 計算の繰り返し上限

# define COLOR_R	"\033[41m"
# define COLOR_OFF	"\033[m"

# define KEY_PRESS	2
# define BUTTON_PRESS	04

// # define KEY_PRESS_MASK	1L<<0
// # define BUTTON_PRESS_MASK	1L<<2
typedef enum e_flag
{
	KEY_PRESS_MASK = 1L<<0,
	BUTTON_PRESS_MASK = 1L<<2,
}			t_flag;

// ここからのマクロは環境によって変わる
// minilibx-linuxディレクトリ内の/test/mlx-testで環境キーコードを確認する。
# define SCROLL_UP	4
# define SCROLL_DOWN	5
# define D	100
# define U	117
# define LEFT_ARROW	65361
# define UP_ARROW	65362
# define RIGHT_ARROW	65363
# define DOWN_ARROW	65364
# define KEY_ESC	65307

// 42Docs引用
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// 複素数
typedef struct s_complex {
	double	real;
	double	imaginary;
}				t_complex;

// img->date
typedef struct s_fractol {
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	t_data		img;
	t_complex	coordinate;
	t_complex	julia_c;
	t_complex	max;
	t_complex	min;
	int			(*draw_target)(struct s_fractol *);
}				t_fract;

// main.cファイル
void		help_fractol(void);
void		check_arguments(t_fract *fract, int argc, char const *argv[]);
bool		ft_isfloat(const char *str);

// ft_atof.cファイル
int			read_sign(char c);
double		ft_atof(const char *nptr);

// init.cファイル
t_complex	complex_init(double real, double imaginary);
void		init_param(t_fract *fract);
bool		init_mlx(t_fract *fract);

// calculate.cファイル
int			my_abs(t_complex complex);
t_complex	proc_fractol(t_complex prev_z, t_complex c);
int			calc_burning_ship(t_fract *fract);
int			calc_mandelbrot_set(t_fract *fract);
int			calc_julia_set(t_fract *fract);

// destroy.cファイル
void		destroy_mlx(t_fract *fract, int exit_status);

// hook.cファイル
void		move(int keycode, t_fract *fract);
int			deal_key(int key_code, t_fract *fract);
void		zoom(int key_code, t_fract *fract);
int			zoom_deal_key(int key_code, int i, int j, t_fract *fract);
void		setting_hooks(t_fract *fract);

// draw.cファイル
int			get_color(int repeat);
void		my_mlx_pixel_put(t_data *img, int x, int y, int color);
void		draw_fractol(t_fract *fract);

#endif
