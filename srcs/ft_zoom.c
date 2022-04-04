/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:23:25 by nflan             #+#    #+#             */
/*   Updated: 2022/04/04 16:43:36 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_limits(int key, t_all *g)
{
	if (g->fractal == 1)
	{
		if (g->zoom <= 30 && key == 5)
		{
			g->zoom = 30;
			return (1);
		}
		if (g->zoom >= 70 && key == 4)
		{
			g->zoom = 70;
			return (1);
		}
	}
	if (g->fractal == 2)
	{
		if (g->zoom <= 26 && key == 5)
		{
			g->zoom = 26;
			return (1);
		}
	}
	return (0);
}

int	ft_zoom(int key, t_all *g)
{
	if (key != 114)
	{
		if (ft_limits(key, g))
			return (1);
		else if (key == 4)
		{
			g->zoom *= 1.1;
			ft_init_zoom(g, 1);
		}
		else if (key == 5)
		{
			g->zoom /= 1.1;
			ft_init_zoom(g, 2);
		}
	}
	else
	{
		if (g->fractal == 1)
			ft_init_mandelbrot(g);
		else
			ft_init_julia(g, g->julia);
	}
	return (0);
}

void	ft_init_zoom(t_all *g, int z)
{
	t_area	tmp;
	int		x;
	int		y;

	tmp = g->area;
	x = g->area.x1 + (g->area.w / 2) * (g->area.x2 - g->area.x1) / g->area.w;
	y = g->area.y1 + (g->area.h / 2) * (g->area.y2 - g->area.y1) / g->area.h;
	if (z == 1)
	{
		g->area.x1 = x - (tmp.x2 - tmp.x1) / 4;
		g->area.x2 = x + (tmp.x2 - tmp.x1) / 4;
		g->area.y1 = y - (tmp.y2 - tmp.y1) / 4;
		g->area.y2 = y + (tmp.y2 - tmp.y1) / 4;
	}
	if (z == 2)
	{
		g->area.x1 = x - (tmp.x2 - tmp.x1);
		g->area.x2 = x + (tmp.x2 - tmp.x1);
		g->area.y1 = y - (tmp.y2 - tmp.y1);
		g->area.y2 = y + (tmp.y2 - tmp.y1);
	}
	g->area.zoom_x = g->area.w / (g->area.x2 - g->area.x1);
	g->area.zoom_y = g->area.h / (g->area.y2 - g->area.y1);
}
