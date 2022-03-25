/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zoom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:23:25 by nflan             #+#    #+#             */
/*   Updated: 2022/03/25 15:24:25 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_limits(int key, t_all *g)
{
	if (g->fractal == 1)
	{
		if (key == 65362 || key == 65364)
			return (1);
		if (g->zoom >= 1.1 && key == 4)
			return (1);
	}
	if (g->fractal == 2)
		if (g->zoom <= 0.2 && key == 5)
			return (1);
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
		g->zoom = 0.8;
	else if (key == 65362)
	{
		if (g->zoom == 0.186276)
			g->zoom = 0.8;
		else
			g->zoom *= 10;
	}
	else if (key == 65364)
	{
		g->zoom /= 10;
		if (g->zoom < 0.186276)
			g->zoom = 0.186276;
	}
	return (0);
}

int	ft_zoom_mandelbrot(int key, t_all *g)
{
	if (key == 4)
		g->zoom += 0.1;
	else if (key == 5)
		g->zoom -= 0.1;
	else if (key == 114)
		g->zoom = 0;
	return (0);
}
