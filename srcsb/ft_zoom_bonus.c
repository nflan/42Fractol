/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:23:25 by nflan             #+#    #+#             */
/*   Updated: 2022/04/01 16:57:30 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

int	ft_limits(int key, t_all *g)
{
	printf("Zoom = %f\n", g->zoom);
	if (g->fractal == 1)
	{
		if (g->zoom <= 20 && key == 5)
		{
			g->zoom = 20;
			return (1);
		}
	}
	if (g->fractal == 2)
	{
		if (g->zoom <= 0.41 && key == 5)
		{
			g->zoom = 0.41;
			return (1);
		}
	}
	return (0);
}

int	ft_zoom(int key, t_all *g)
{
	if (key != 114)
		if (ft_limits(key, g))
			return (1);
	if (g->fractal == 1)
		ft_zoom_mandelbrot(key, g);
	else
		ft_zoom_julia(key, g);
	return (0);
}

int	ft_zoom_julia(int key, t_all *g)
{
	if (key == 4)
		g->zoom *= 1.1;
	else if (key == 5)
		g->zoom /= 1.1;
	else if (key == 114)
		ft_init_julia(g, g->julia);
	return (0);
}

int	ft_zoom_mandelbrot(int key, t_all *g)
{
	if (key == 4 || key == 65431)
		g->zoom *= 1.5;
	else if (key == 5 || key == 65437)
		g->zoom /= 1.5;
	else if (key == 114)
		ft_init_mandelbrot(g);	
	return (0);
}
