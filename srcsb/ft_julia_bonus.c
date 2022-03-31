/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:18:15 by nflan             #+#    #+#             */
/*   Updated: 2022/03/31 19:13:40 by nflan            ###   ########.fr       */
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
	g->posx = 0;
	g->posy = 0;
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
	t_area	tmp;
	double	X;
	double	Y;

	tmp = g->area;
	X = g->area.x1 + g->mousex * (g->area.x2 - g->area.x1) / g->area.w;
	Y = g->area.y1 + g->mousey * (g->area.y2 - g->area.y1) / g->area.h;
	printf("X = %f && Y = %f\n", X, Y);
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

/*void	ft_init_zoom_julia(t_all *g, int z)
{
	t_area	tmp;
	double	X;
	double	Y;

//	X = g->posx + g->mousex * (g->c.im - g->c.re) / g->area.w;
//	Y = g->posy + g->mousey * (g->c.im - g->c.re) / g->area.h;
//	X = (g->posx + g->c.re) + g->mousex * ((g->posx + g->c.im) - (g->posx + g->c.re)) / g->area.w;
//	Y = (g->posy + g->c.re) + g->mousey * ((g->posy + g->c.im) - (g->posy + g->c.re)) / g->area.h;
//	X = g->mousex / g->area.zoom_x;//(g->c.im - g->c.re) / g->area.w;
//	Y = g->mousey / g->area.zoom_y;//(g->c.im - g->c.re) / g->area.h;
//	Y = g->mousey - g->area.h / 2;
	printf("g->zoom = %f\n", g->zoom);
	printf("mousex = %f && mousey = %f\n", g->mousex, g->mousey);
//	printf("g->area.zoom_x = %f &&", g->area.zoom_x);
//	printf("g->area.zoom_y = %f\n", g->area.zoom_y);
//	printf("g->area.w = %d &&", g->area.w);
//	printf("g->area.h = %d\n", g->area.h);
//	printf("g->area.w - g->area.zoom_x = %f && g->area.h - g->area.zoom_y = %f\n", (double) g->area.w - g->area.zoom_x, (double) g->area.h - g->area.zoom_y);
	tmp = g->area;
//	X = g->posx + g->mousex / (0.5 * g->zoom * g->area.w);// * ((double) g->area.zoom_x / 2) / g->area.w;//zoom_x;
//	Y = ig->posy + g->mousey / (0.5 * g->zoom * g->area.h);// * ((double) g->area.zoom_x / 2) / g->area.w;//zoom_x;
	//Y = g->mousey / (g->area.zoom_y);/ ((double) g->area.zoom_y / 2) / g->area.h;//zoom_y;
	X = g->posx + g->mousex / (g->area.w / 2);
	Y = g->posy + g->mousey / (g->area.h / 2);
	if (z == 1)
	{
	//	g->posx = X / g->zoom;// + 0.5;// / g->zoom + 1;// - (g->c.im - g->c.re) / 4;
	//	g->posy = Y / g->zoom;// + 0.5; // g->zoom + 1;// + (g->c.im - g->c.re) / 4;
//		g->posx = (X - (g->c.im - g->c.re)) / g->area.zoom_x;
//		g->posy = (Y - (g->c.im - g->c.re)) / g->area.zoom_y;
		g->area.x1 = X - (tmp.x2 - tmp.x1) / 4;
		g->area.x2 = X + (tmp.x2 - tmp.x1) / 4;
		g->area.y1 = Y - (tmp.y2 - tmp.y1) / 4;
		g->area.y2 = Y + (tmp.y2 - tmp.y1) / 4;

	}
	if (z == 2)
	{
		g->posx = X - (g->c.im - g->c.re);
		g->posy = Y - (g->c.im - g->c.re);
	//	g->posx = X + 1;// - (g->c.im - g->c.re);
	//	g->posy = Y + 1;//+ (g->c.im - g->c.re);
	}
//	printf("0.5 * g->zoom * g->area.w = %f\n", 0.5 * g->zoom * g->area.w);
//	printf("0.5 / g->zoom / g->area.zoom_z = %f\n", 0.5 / g->zoom / g->area.zoom_x);
//	printf("0.5 * g->zoom = %f\n", 0.5 * g->zoom);
	printf("X = %f && Y = %f\n", X, Y);
	g->posx = X - 1;// - (g->c.im - g->c.re) * g->zoom;// - 1.25;// - 0.5 * g->zoom;
	g->posy = Y - 1;// - (g->c.im - g->c.re) * g->zoom;// - 1.25;// - 0.5 * g->zoom;
	printf("posx = %f && posy = %f\n", g->posx, g->posy);
//	printf("g->area.x1 = %f && g->area.x2 = %f\n", g->area.x1, g->area.x2);
//	printf("g->area.y1 = %f && g->area.y2 = %f\n", g->area.y1, g->area.y2);
	g->area.zoom_x = 0.5 * g->zoom * g->area.w;
	g->area.zoom_y = 0.5 * g->zoom * g->area.h;
}*/

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
			z.re = 1.5 * (g->x - g->area.w / 2) / g->area.zoom_x + g->area.x1 + g->area.x2;
			z.im = (g->y - g->area.h / 2) / g->area.zoom_y + g->area.y1 + g->area.y2;
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
