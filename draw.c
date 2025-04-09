/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:43:55 by hlamhans          #+#    #+#             */
/*   Updated: 2025/04/07 16:14:10 by hlamhans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	calculate_mandelbrot(t_fractal *fractal)
{
	int			i;
	double		tem;

	i = 1;
	fractal->zx = 0;
	fractal->zy = 0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->shift_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->shift_y;
	while (++i < fractal->iteration)
	{
		tem = fractal->zx * fractal->zx - fractal->zy
			* fractal->zy + fractal->cx;
		fractal->zy = 2 * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = tem;
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy) > 4)
			break ;
	}
	if (i == fractal->iteration)
		my_pixel_put(fractal->x, fractal->y, &fractal->img, 0x000000);
	else
		my_pixel_put(fractal->x, fractal->y,
			&fractal->img, (fractal->color * (i % 255)));
}

void	calculate_julia(t_fractal *fractal)
{
	double	tem;
	int		i;

	i = 1;
	fractal->cx = fractal->julia_x;
	fractal->cy = fractal->julia_y;
	fractal->zx = (fractal->x / fractal->zoom) + fractal->shift_x;
	fractal->zy = (fractal->y / fractal->zoom) + fractal->shift_y;
	while (i < fractal->iteration)
	{
		tem = fractal->zx * fractal->zx - fractal->zy
			* fractal->zy + fractal->cx;
		fractal->zy = 2 * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = tem;
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy) > 4)
			break ;
		i++;
	}
	if (i == fractal->iteration)
		my_pixel_put(fractal->x, fractal->y, &fractal->img, 0x000000);
	else
		my_pixel_put(fractal->x, fractal->y,
			&fractal->img, (fractal->color * (i % 255)));
}

void	calculate_burning_ship(t_fractal *fractal)
{
	int			i;
	double		tem;

	i = 1;
	fractal->zx = 0;
	fractal->zy = 0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->shift_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->shift_y;
	while (++i < fractal->iteration)
	{
		tem = fractal->zx * fractal->zx - fractal->zy
			* fractal->zy + fractal->cx;
		fractal->zy = fabs(2 * fractal->zx * fractal->zy + fractal->cy);
		fractal->zx = fabs(tem);
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy) > 4)
			break ;
	}
	if (i == fractal->iteration)
		my_pixel_put(fractal->x, fractal->y, &fractal->img, 0x000000);
	else
		my_pixel_put(fractal->x, fractal->y,
			&fractal->img, (fractal->color * (i % 255)));
}

void	calc_tricorn(t_fractal *fractal)
{
	int			i;
	double		tem;

	i = 1;
	fractal->zx = 0;
	fractal->zy = 0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->shift_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->shift_y;
	while (++i < fractal->iteration)
	{
		tem = fractal->zx * fractal->zx - fractal->zy
			* fractal->zy + fractal->cx;
		fractal->zy = -2 * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = tem;
		if ((fractal->zx * fractal->zx) + (fractal->zy * fractal->zy) > 4)
			break ;
	}
	if (i == fractal->iteration)
		my_pixel_put(fractal->x, fractal->y, &fractal->img, 0x000000);
	else
		my_pixel_put(fractal->x, fractal->y,
			&fractal->img, (fractal->color * (i % 255)));
}

void	fractal_draw(t_fractal *fractal)
{
	fractal->x = 0;
	while (fractal->x < HEIGHT)
	{
		fractal->y = 0;
		while (fractal->y < WIDTH)
		{
			if (ft_strcmp(fractal->name, "mandelbrot") == 0)
				calculate_mandelbrot(fractal);
			else if (ft_strcmp(fractal->name, "burning_ship") == 0)
				calculate_burning_ship(fractal);
			else if (ft_strcmp(fractal->name, "julia") == 0)
				calculate_julia(fractal);
			else if (ft_strcmp(fractal->name, "tricorn") == 0)
				calc_tricorn(fractal);
			fractal->y++;
		}
		fractal->x++;
	}
	mlx_put_image_to_window(fractal->mlx_connection,
		fractal->mlx_window,
		fractal->img.img,
		0,
		0);
}
