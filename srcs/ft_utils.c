/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:24:57 by nflan             #+#    #+#             */
/*   Updated: 2022/03/25 17:40:34 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_input(int keycode, t_all *g)
{
	int	i;

	i = 100;
	if (keycode == 65361 || keycode == 65363)
		ft_change_color(keycode, g);
	else if (keycode == 98)
		while (i-- > 0)
			ft_change_color(65363, g);
	else if (keycode == 106 || keycode == 109)
		ft_change(keycode, g);
	else if (keycode == 113 || keycode == 65307)
		ft_destroy_win(g);
	else if (keycode == 114 || keycode == 65362 || keycode == 65364)
		if (ft_zoom(keycode, g))
			return (1);
	if ((keycode >= 65450 && keycode <= 65455) || keycode == 65469)
		ft_net(keycode, g);
	else if (keycode >= 48 && keycode <= 57 && g->fractal == 2)
		ft_init_julia(g, keycode);
	ft_print_new(g);
	return (0);
}

int	ft_mouse(int keycode, int x, int y, t_all *g)
{
	(void)x;
	(void)y;
	if (keycode == 4 || keycode == 5)
		if (ft_zoom(keycode, g))
			return (1);
	ft_print_new(g);
	return (0);
}

int	ft_net(int key, t_all *g)
{
	if (key == 65450)
		g->max += 50;
	else if (key == 65451)
		g->max += 5;
	else if (key == 65453)
		g->max -= 5;
	else if (key == 65455)
		g->max -= 50;
	else if (key == 65469)
	{
		if (g->fractal == 1 || (g->fractal == 2
				&& g->julia > 0 && g->julia < 4))
			g->max = 50;
		else if (g->julia == 0)
			g->max = 300;
		else if (g->julia > 3 && g->julia < 7)
			g->max = 100;
		else if (g->julia > 6 && g->julia < 9)
			g->max = 150;
		else
			g->max = 200;
	}
	if (g->max <= 5 || g->max >= 429496)
		g->max = 5;
	return (0);
}

int	ft_change(int key, t_all *g)
{
	if (key == 106 && g->fractal != 2)
		ft_init_julia(g, g->julia);
	else if (key == 109 && g->fractal != 1)
		ft_init_mandelbrot(g);
	return (0);
}

int	ft_print_new(t_all *g)
{
	g->curr.img = mlx_new_image(g->setup, g->width, g->height);
	g->curr.addr = mlx_get_data_addr(g->curr.img, &g->curr.bits_per_pixel,
			&g->curr.line_length, &g->curr.endian);
	if (g->fractal == 1)
		ft_mandelbrot(g, g->curr);
	else
		ft_julia(g, g->curr);
	mlx_destroy_image(g->setup, g->img.img);
	mlx_clear_window(g->setup, g->window);
	g->img = g->curr;
	mlx_put_image_to_window(g->setup, g->window, g->img.img, 0, 0);
	return (0);
}
