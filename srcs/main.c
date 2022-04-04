/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/04/04 16:49:32 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(int ac, char **av)
{
	t_all	*g;

	g = NULL;
	ft_parse(ac, av, 0);
	g = ft_init_all(av);
	if (g)
	{
		g->img = ft_init_img(g);
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
