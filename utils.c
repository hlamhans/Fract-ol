/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:48:18 by hlamhans          #+#    #+#             */
/*   Updated: 2025/04/07 15:48:43 by hlamhans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_pixel_put(int x, int y, t_image *img, int color)
{
	int	*buffer;

	buffer = (int *)img->addr;
	buffer[(y * img->len * 8 / img->bbp) + x] = color;
}

void	show_help(void)
{
	print("\n", 1);
	print(" +------------------- Let me help you! -----------------+\n", 1);
	print(" |                                                      |\n", 1);
	print(" | Usage: ./fractol [mandelbrot /burning_ship ", 1);
	print("/tricorn] |\n", 1);
	print(" | Usage: ./fractol [julia <value 1> <value 2>]         |\n", 1);
	print(" |                                                      |\n", 1);
	print(" |------------------------- KEYBOARD -------------------|\n", 1);
	print(" |                                                      |\n", 1);
	print(" | Press ESC to close the window                        |\n", 1);
	print(" | Press one of [1-9] to change the color of fractal    |\n", 1);
	print(" | Use mouse scroll to zoom in and out of the fractal   |\n", 1);
	print(" | Press the arrow keys to change the viewpoint         |\n", 1);
	print(" | Press [Space] to reset the fractal                   |\n", 1);
	print(" +------------------------------------------------------+\n", 1);
}

void	print(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		++i;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

long double	atodbl(char *s)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	pow = 1;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		++s;
	if (*s == '+' || *s == '-')
	{
		if (*s++ == '-')
			sign = -1;
	}
	while (*s != '.' && *s)
		integer_part = (integer_part * 10) + (*s++ - '0');
	if (*s == '.')
		while (*++s)
			fractional_part += ((*s - '0') * (pow /= 10));
	return ((integer_part + fractional_part) * sign);
}
