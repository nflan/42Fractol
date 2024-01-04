/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:18:14 by nflan             #+#    #+#             */
/*   Updated: 2022/04/04 16:46:42 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_julia_tool(t_all *g, double re, double im, int max)
{
	int	i;

	i = 0;
	g->c.re = re;
	g->c.im = im;
	g->max = max;
	g->area.x1 = -1.25;
	g->area.x2 = 1.25;
	g->area.y1 = -1.25;
	g->area.y2 = 1.25;
	if (g->julia >= 48 && g->julia <= 58)
		while (i++ < 10)
			if (i + 48 == g->julia)
				g->julia = i;
	g->area.w = g->width;
	g->area.h = g->height;
	while ((double)g->area.w / (double)g->area.h != 1.3)
	{
		if ((double)g->area.w / (double)g->area.h > 1.3)
			g->area.w--;
		if ((double)g->area.w / (double)g->area.h < 1.3)
			g->area.h--;
	}
	g->area.zoom_x = g->area.w / (g->area.x2 - g->area.x1);
	g->area.zoom_y = g->area.h / (g->area.y2 - g->area.y1);
}

void	ft_init_julia(t_all *g, int e)
{
	g->julia = e;
	g->zoom = 50;
	g->fractal = 2;
	if (e == 0 || e == 48)
		ft_julia_tool(g, -0.7, 0.27015, 300);
	else if (e == 1 || e == 49)
		ft_julia_tool(g, -0.4, 0.582, 50);
	else if (e == 2 || e == 50)
		ft_julia_tool(g, -1.25, 0, 50);
	else if (e == 3 || e == 51)
		ft_julia_tool(g, 0.44, 0.25, 50);
	else if (e == 4 || e == 52)
		ft_julia_tool(g, -0.56, 0.645, 100);
	else if (e == 5 || e == 53)
		ft_julia_tool(g, -0.514, 0.58, 100);
	else if (e == 6 || e == 54)
		ft_julia_tool(g, -1.414, 0, 100);
	else if (e == 7 || e == 55)
		ft_julia_tool(g, 0.32, 0.035, 150);
	else if (e == 8 || e == 56)
		ft_julia_tool(g, 0.285, 0.01, 150);
	else if (e == 9 || e == 57)
		ft_julia_tool(g, -0.1, 0.65, 200);
}

void	ft_check_julia(t_all *g)
{
	if (g->max >= 3200)
		g->max = 3200;
	g->fractal = 2;
	g->y = 0;
	g->posx = (g->area.x1 + g->area.x2) / 2;
	g->posy = (g->area.y1 + g->area.y2) / 2;
}

void	ft_julia(t_all *g, t_data img)
{
	t_complex		z;
	unsigned int	iteration;

	ft_check_julia(g);
	while (g->y++ < g->area.h)
	{
		g->x = 0;
		while (g->x++ < g->area.w)
		{
			z.re = 1.5 * (g->x - g->area.w / 2) / g->area.zoom_x + g->posx;
			z.im = (g->y - g->area.h / 2) / g->area.zoom_y + g->posy;
			iteration = 0;
			while (z.re * z.re + z.im * z.im < 4 && iteration < g->max)
			{
				z.tmpre = z.re;
				z.re = z.tmpre * z.tmpre - z.im * z.im + g->c.re;
				z.im = z.im * z.tmpre + z.im * z.tmpre + g->c.im;
				iteration++;
			}
			if (iteration != g->max)
				my_mlx_pixel_put(&img, g, ft_deg(iteration, g, g->color));
		}
	}
}
