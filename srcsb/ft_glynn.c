/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glynn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:23:19 by nflan             #+#    #+#             */
/*   Updated: 2022/04/05 12:31:58 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	ft_init_glynn(t_all *g)
{
	g->zoom = 50;
	g->max = 30;
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
	g->area.x1 = -1;
	g->area.x2 = 1;
	g->area.y1 = -0.9;
	g->area.y2 = 0.9;
	g->area.zoom_x = g->area.w / (g->area.x2 - g->area.x1);
	g->area.zoom_y = g->area.h / (g->area.y2 - g->area.y1);
}

void	ft_check_glynn(t_all *g)
{
	if (g->max >= 3800)
		g->max = 3800;
	g->c.re = 0.291;
	g->c.im = 0.006;
	g->fractal = 3;
	g->x = 0;
}

void	ft_glynn(t_all *g, t_data img)
{
	t_complex		z;
	unsigned int	iteration;

	ft_check_glynn(g);
	while (g->x++ < g->area.w)
	{
		g->y = 0;
		while (g->y++ < g->area.h)
		{
			z.re = g->x / g->area.zoom_x + g->area.x1;
			z.im = g->y / g->area.zoom_y + g->area.y1;
			iteration = 0;
			while (z.re * z.re + z.im * z.im < 4 && iteration < g->max)
			{
				z.tmpre = z.re;
				z.re = sqrt((z.re * z.re - z.im * z.im) * (z.re * z.re
							- z.im * z.im)) + g->c.re;
				z.im = sqrt((2 * z.tmpre * z.im) * (z.im * z.tmpre * 2))
					+ g->c.im;
				iteration++;
			}
			if (iteration != g->max)
				my_mlx_pixel_put(&img, g, ft_deg(iteration, g, g->color));
		}
	}
}
