/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dragon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:23:19 by nflan             #+#    #+#             */
/*   Updated: 2022/04/04 17:40:02 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	ft_init_dragon(t_all *g)
{
	g->zoom = 50;
	g->max = 70;
	g->fractal = 3;
	g->area.w = g->width;
	g->area.h = g->height;
	while ((double)g->area.w / (double)g->area.h != 1.125)
	{
		if ((double)g->area.w / (double)g->area.h > 1.125)
			g->area.w--;
		if ((double)g->area.w / (double)g->area.h < 1.125)
			g->area.h--;
	}
	g->area.x1 = 0;
	g->area.x2 = 1;
	g->area.y1 = 1;
	g->area.y2 = 0;
	g->area.zoom_x = g->area.w / (g->area.x2 - g->area.x1);
	g->area.zoom_y = g->area.h / (g->area.y2 - g->area.y1);
}

void	ft_check_dragon(t_all *g)
{
	if (g->max >= 3800)
		g->max = 3800;
	g->fractal = 3;
	g->x = 0;
}

void	ft_dragon(t_all *g, t_data img)
{
	t_complex		z;
	unsigned int	iteration;

	ft_check_dragon(g);
	while (g->x++ < g->area.w)
	{
		g->y = 0;
		while (g->y++ < g->area.h)
		{
			g->c.re = g->x / g->area.zoom_x + g->area.x1;
			g->c.im = g->y / g->area.zoom_y + g->area.y1;
			z.im = 0;
			z.re = 0;
			iteration = 0;
			while (z.re * z.re + z.im * z.im < 4 && iteration < g->max)
			{
				z.tmpre = z.re * z.re - z.im * z.im + g->c.re;
				z.im = z.im * z.re + z.im * z.re + g->c.im;
				z.re = z.tmpre;
				iteration++;
			}
			if (iteration != g->max)
				my_mlx_pixel_put(&img, g, ft_deg(iteration, g, g->color));
		}
	}
}
