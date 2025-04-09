/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamhans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:42:19 by hlamhans          #+#    #+#             */
/*   Updated: 2025/04/08 09:01:54 by hlamhans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	valid(const char *str)
{
	int	has_dot;
	int	has_digit;

	has_dot = 0;
	has_digit = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (ft_isdigit(*str))
			has_digit = 1;
		else
			return (0);
		str++;
	}
	return (has_digit);
}

static int	check(char *str)
{
	if (!ft_strcmp(str, "mandelbrot") || !ft_strcmp(str, "burning_ship")
		|| !ft_strcmp(str, "tricorn") || !ft_strcmp(str, "julia"))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((ac == 2 || ac == 4) && check(av[1]))
	{
		fractal.name = av[1];
		if (ac == 4 && !ft_strcmp(av[1], "julia"))
		{
			if (!valid(av[2]) || !valid(av[3]))
			{
				print("\nError: Julia parameters must be valid float.\n", 2);
				return (0);
			}
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		fractol_init(&fractal);
		fractal_draw(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
		show_help();
	return (0);
}
