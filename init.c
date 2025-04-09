/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:41:26 by hlamhans          #+#    #+#             */
/*   Updated: 2025/04/07 15:53:24 by hlamhans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	malloc_error(void)
{
	write(2, "error with allocation", 22);
	return ;
}

void	data_init(t_fractal *fractal)
{
	fractal->zoom = 200;
	fractal->x = 0;
	fractal->y = 0;
	fractal->iteration = 69;
	fractal->shift_x = -2;
	fractal->shift_y = -2;
	fractal->color = 0xC000FF;
}

void	event_init(t_fractal *fractal)
{
	mlx_key_hook(fractal->mlx_window, keyboard_handle, fractal);
	mlx_mouse_hook(fractal->mlx_window, mouse_handler, fractal);
	mlx_hook(fractal->mlx_window, 17, 0L, close_window, fractal);
}

void	fractol_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection, WIDTH, HEIGHT,
			fractal->name);
	if (fractal->mlx_window == NULL)
	{
		free_resources(fractal);
		malloc_error();
	}
	fractal->img.img = mlx_new_image(fractal->mlx_connection, WIDTH, HEIGHT);
	if (fractal->img.img == NULL)
	{
		free_resources(fractal);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img, &fractal->img.bbp,
			&fractal->img.len, &fractal->img.endian);
	if (fractal->img.addr == NULL)
	{
		free_resources(fractal);
		malloc_error();
	}
	data_init(fractal);
	event_init(fractal);
}

void	free_resources(t_fractal *fractal)
{
	if (fractal->img.img != NULL)
	{
		mlx_destroy_image(fractal->mlx_connection, fractal->img.img);
	}
	if (fractal->mlx_window != NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	}
	if (fractal->mlx_connection != NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
	}
}
