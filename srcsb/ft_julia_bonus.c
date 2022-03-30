/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:18:15 by nflan             #+#    #+#             */
/*   Updated: 2022/03/30 15:35:51 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

void	ft_julia_tool(t_all *g, double re, double im, int max)
{
	int	i;

	i = 0;
	g->c.re = re;
	g->c.im = im;
	g->max = max;
	g->posx = 1;
	g->posy = 1;
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
	g->area.zoom_x = 0.5 * g->zoom * g->area.w;
	g->area.zoom_y = 0.5 * g->zoom * g->area.h;
}

void	ft_init_julia(t_all *g, int e)
{
	g->julia = e;
	g->zoom = 0.8;
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
	g->fractal = 2;
}

void	ft_init_zoom_julia(t_all *g, int z)
{
	double	X;
	double	Y;
	X = g->c.re + g->mousex * (g->c.im - g->c.re) / g->area.w;
	Y = g->c.re + g->mousey * (g->c.im - g->c.re) / g->area.h;
	printf("X = %f\n", X);
	printf("Y = %f\n", Y);
	if (z == 1)
	{
		g->posx = X / 4 + 1;// - (g->c.im - g->c.re) / 4;
		g->posy = Y / 4 + 1;// + (g->c.im - g->c.re) / 4;
	}
	if (z == 2)
	{
		g->posx = X + 1;// - (g->c.im - g->c.re);
		g->posy = Y + 1;//+ (g->c.im - g->c.re);
	}
	g->area.zoom_x = 0.5 * g->zoom * g->area.w;
	g->area.zoom_y = 0.5 * g->zoom * g->area.h;
}

void	ft_check_julia(t_all *g)
{
	if (g->max >= 3200)
		g->max = 3200;
	g->fractal = 2;
	g->y = 0;
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
			z.re = 1.5 * (g->x - g->area.w / 2) / g->area.zoom_x + g->posx - 1;
			z.im = (g->y - g->area.h / 2) / g->area.zoom_y + g->posy - 1;
			iteration = 0;
			while (z.re * z.re + z.im * z.im <= 4 && iteration < g->max)
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
