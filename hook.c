/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:40:04 by hlamhans          #+#    #+#             */
/*   Updated: 2025/04/07 16:15:06 by hlamhans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	change_color(int keysym, t_fractal *fractal)
{
	if (keysym == XK_1)
		fractal->color += 0x030000;
	else if (keysym == XK_2)
		fractal->color += 0x003000;
	else if (keysym == XK_3)
		fractal->color += 0x000300;
	else if (keysym == XK_4)
		fractal->color += 0x000030;
	else if (keysym == XK_5)
		fractal->color -= 0x300000;
	else if (keysym == XK_6)
		fractal->color -= 0x030000;
	else if (keysym == XK_7)
		fractal->color -= 0x003000;
	else if (keysym == XK_8)
		fractal->color -= 0x000300;
	else if (keysym == XK_9)
		fractal->color -= 0x000030;
}

void	zoom(t_fractal *fractal, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 2;
	if (zoom == 1)
	{
		fractal->shift_x = (x / fractal->zoom + fractal->shift_x) - (x
				/ (fractal->zoom * zoom_level));
		fractal->shift_y = (y / fractal->zoom + fractal->shift_y) - (y
				/ (fractal->zoom * zoom_level));
		fractal->zoom *= zoom_level;
	}
	else if (zoom == -1)
	{
		fractal->shift_x = (x / fractal->zoom + fractal->shift_x) - (x
				/ (fractal->zoom / zoom_level));
		fractal->shift_y = (y / fractal->zoom + fractal->shift_y) - (y
				/ (fractal->zoom / zoom_level));
		fractal->zoom /= zoom_level;
	}
	else
		return ;
}

int	close_window(t_fractal	*fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connection);
	free(fractal->mlx_connection);
	exit(0);
}

int	keyboard_handle(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
	{
		close_window(fractal);
	}
	else if (keysym == XK_Left)
		fractal->shift_x += 0.1;
	else if (keysym == XK_Right)
		fractal->shift_x -= 0.1;
	else if (keysym == XK_Up)
		fractal->shift_y += 0.1;
	else if (keysym == XK_Down)
		fractal->shift_y -= 0.1;
	else if (keysym == XK_space)
		data_init(fractal);
	else
	{
		change_color(keysym, fractal);
	}
	fractal_draw(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == 5)
	{
		zoom(fractal, x, y, 1);
		fractal_draw(fractal);
	}
	else if (button == 4)
	{
		zoom(fractal, x, y, -1);
		fractal_draw(fractal);
	}
	return (0);
}
