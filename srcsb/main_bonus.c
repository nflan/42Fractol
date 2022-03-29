/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/03/29 15:52:35 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

int	main(int ac, char **av)
{
	t_all	*g;

	ft_parse(ac, av, 0);
	g = ft_init_all(av);
	if (g)
	{
		g->img.img = mlx_new_image(g->setup, g->width, g->height);
		g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
				&g->img.line_length, &g->img.endian);
		if (g->fractal == 2)
			ft_julia(g, g->img);
		else
			ft_mandelbrot(g, g->img);
		mlx_put_image_to_window(g->setup, g->window, g->img.img, 0, 0);
		mlx_hook(g->window, 2, 1L << 0, ft_input, g);
		mlx_hook(g->window, 4, 1L << 2, ft_mouse, g);
		mlx_hook(g->window, 17, 0, ft_destroy_win, g);
		mlx_loop(g->setup);
	}
	return (0);
}
