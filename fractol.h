/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:53 by hlamhans          #+#    #+#             */
/*   Updated: 2025/04/07 15:41:10 by hlamhans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

typedef struct s_image
{
	void	*img;
	void	*addr;
	int		bbp;
	int		len;
	int		endian;

}			t_image;
typedef struct s_fractal
{
	void	*mlx_connection;
	void	*mlx_window;
	char	*name;
	t_image	img;
	int		iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	double	julia_x;
	double	julia_y;
	int		color;
	int		x;
	int		y;
}			t_fractal;

void		fractol_init(t_fractal *fractal);
void		free_resources(t_fractal *fractal);
void		fractal_draw(t_fractal *fractal);
void		calculate_mandelbrot(t_fractal *fractal);
void		calculate_burning_ship(t_fractal *fractal);
void		calculate_julia(t_fractal *fractal);
int			keyboard_handle(int key_num, t_fractal *fractal);
void		data_init(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
long double	atodbl(char *s);
int			ft_strcmp(char *s1, char *s2);
int			close_window(t_fractal	*fractal);
void		show_help(void);
void		print(char *s, int fd);
void		calc_tricorn(t_fractal *fractal);
void		my_pixel_put(int x, int y, t_image *img, int color);
#endif
