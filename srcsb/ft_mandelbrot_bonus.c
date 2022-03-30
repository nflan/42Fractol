/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:22:13 by nflan             #+#    #+#             */
/*   Updated: 2022/03/30 15:21:24 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	ft_init_mandelbrot(t_all *g)
{
	g->zoom = 400;
	g->max = 50;
	g->fractal = 1;
	g->area.w = g->width;
	g->area.h = g->height;
	while ((double)g->area.w / (double)g->area.h != 1.125)
	{
		if ((double)g->area.w / (double)g->area.h > 1.125)
			g->area.w--;
		if ((double)g->area.w / (double)g->area.h < 1.125)
			g->area.h--;
	}
	g->area.x1 = -2.1;
	g->area.x2 = 0.6;
	g->area.y1 = -1.2;
	g->area.y2 = 1.2;
	g->area.zoom_x = g->area.w / (g->area.x2 - g->area.x1);
	g->area.zoom_y = g->area.h / (g->area.y2 - g->area.y1);
}

void	ft_init_zoom_mandelbrot(t_all *g, int z)
{
	t_area	tmp;
	double	X;
	double	Y;

	tmp = g->area;
	X = g->area.x1 + g->mousex * (g->area.x2 - g->area.x1) / g->area.w;
	Y = g->area.y1 + g->mousey * (g->area.y2 - g->area.y1) / g->area.h;
	printf("x = %f\n", X);
	if (z == 1)
	{
		g->area.x1 = X - (tmp.x2 - tmp.x1) / 4;
		g->area.x2 = X + (tmp.x2 - tmp.x1) / 4;
		g->area.y1 = Y - (tmp.y2 - tmp.y1) / 4;
		g->area.y2 = Y + (tmp.y2 - tmp.y1) / 4;
	}
	if (z == 2)
	{
		g->area.x1 = X - (tmp.x2 - tmp.x1);
		g->area.x2 = X + (tmp.x2 - tmp.x1);
		g->area.y1 = Y - (tmp.y2 - tmp.y1);
		g->area.y2 = Y + (tmp.y2 - tmp.y1);
	}
	g->area.zoom_x = g->area.w / (g->area.x2 - g->area.x1);
	g->area.zoom_y = g->area.h / (g->area.y2 - g->area.y1);
}

void	ft_check_mandelbrot(t_all *g)
{
	if (g->max >= 3800)
		g->max = 3800;
	g->fractal = 1;
	g->x = 0;
}

void	ft_mandelbrot(t_all *g, t_data img)
{
	t_complex		z;
	unsigned int	iteration;

	printf("g->zoom = %f\n", g->zoom);
	ft_check_mandelbrot(g);
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
