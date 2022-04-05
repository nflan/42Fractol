/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/04/05 12:09:02 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

int	main(int ac, char **av)
{
	t_all	*g;

	g = NULL;
	ft_parse(ac, av, 0);
	g = ft_init_all(av);
	if (g)
	{
		g->img = ft_init_img(g);
		if (g->fractal == 1)
			ft_mandelbrot(g, g->img);
		else if (g->fractal == 2)
			ft_julia(g, g->img);
		else
			ft_glynn(g, g->img);
		mlx_put_image_to_window(g->setup, g->window, g->img.img, 0, 0);
		mlx_hook(g->window, 2, 1L << 0, ft_input, g);
		mlx_hook(g->window, 4, 1L << 2, ft_mouse, g);
		mlx_hook(g->window, 17, 0, ft_destroy_win, g);
		mlx_loop(g->setup);
	}
	return (0);
}
