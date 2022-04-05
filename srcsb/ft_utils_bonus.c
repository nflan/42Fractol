/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:24:57 by nflan             #+#    #+#             */
/*   Updated: 2022/04/05 12:34:07 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	ft_move(int key, t_all *g)
{
	double	x;
	double	y;

	x = (g->area.x2 - g->area.x1) / 4;
	y = (g->area.y2 - g->area.y1) / 4;
	if (key == 65361)
	{
		g->area.x1 -= x;
		g->area.x2 -= x;
	}
	else if (key == 65362)
	{
		g->area.y1 -= y;
		g->area.y2 -= y;
	}
	else if (key == 65363)
	{
		g->area.x1 += x;
		g->area.x2 += x;
	}
	else
	{
		g->area.y1 += y;
		g->area.y2 += y;
	}
}

int	ft_input(int keycode, t_all *g)
{
	if (keycode == 65430 || keycode == 65432)
		return (ft_change_color(keycode, g));
	else if (keycode == 98)
	{
		while (keycode-- > 0)
			ft_change_color(65432, g);
		return (0);
	}
	else if (keycode == 106 || keycode == 109 || keycode == 103)
		ft_change(keycode, g);
	else if (keycode >= 65361 && keycode <= 65364)
		ft_move(keycode, g);
	else if (keycode == 113 || keycode == 65307)
		ft_destroy_win(g, 0);
	else if (keycode == 114)
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
	g->mousex = (double) x - ((double)g->width - (double)g->area.w) / 2;
	g->mousey = (double) y - ((double)g->height - (double)g->area.h) / 2;
	if (g->mousex <= 0)
		g->mousex = 0;
	if (g->mousex >= g->area.w)
		g->mousex = g->area.w;
	if (g->mousey <= 0)
		g->mousey = 0;
	if (g->mousey >= g->area.h)
		g->mousey = g->area.h;
	if (keycode == 4 || keycode == 5)
	{
		if (ft_zoom(keycode, g))
			return (1);
		if (keycode == 4)
			ft_init_zoom(g, 1);
		if (keycode == 5)
			ft_init_zoom(g, 2);
		ft_print_new(g);
	}
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
	if (key == 109 && g->fractal != 1)
		ft_init_mandelbrot(g);
	else if (key == 106 && g->fractal != 2)
		ft_init_julia(g, g->julia);
	else if (key == 103 && g->fractal != 3)
		ft_init_glynn(g);
	return (0);
}
