/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:41:20 by nflan             #+#    #+#             */
/*   Updated: 2022/03/28 18:51:41 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

int	ft_rgb_psy(t_all *g, int iteration)
{
	int	r;
	int	gg;
	int	b;
	int	i;

	r = 0;
	gg = 0;
	b = 0;
	i = g->max / 7;
	if (iteration < i * 2)
		return (create_trgb(100, iteration, iteration, iteration));
	if (iteration < i * 3)
		b = iteration * i;
	else if (iteration < i * 4)
		gg = iteration * i;
	else if (iteration < i * 5)
		return (create_trgb(100, iteration * i, iteration * i, b));
	else if (iteration < i * 6)
		return (create_trgb(100, iteration * i, iteration * i / 2, b));
	else if (iteration < i * 7)
		return (create_trgb(100, iteration * i, gg, b));
	return (create_trgb(100, r, gg, b));
}

int	ft_red_psy(t_all *g, int iteration)
{
	int	r;
	int	gg;
	int	b;
	int	i;

	r = 0;
	gg = 0;
	b = 0;
	i = g->max / 7;
	if (iteration < i * 2)
		return (create_trgb(100, iteration, iteration, iteration));
	if (iteration < i * 3)
		b = 255 - iteration * i;
	else if (iteration < i * 4)
		gg = 255 - iteration * i;
	else if (iteration < i * 5)
		return (create_trgb(100, 255 - iteration * i, 255 - iteration * i, b));
	else if (iteration < i * 6)
	{
		r = 255 - iteration * i;
		gg = 255 - iteration * i / 2;
	}
	else if (iteration < i * 7)
		r = 255 - iteration * i;
	return (create_trgb(100, r, gg, b));
}

int	ft_rgb(t_all *g, int iteration)
{
	int	r;
	int	gg;
	int	b;
	int	i;

	r = 0;
	gg = 0;
	b = 0;
	i = g->max / 7;
	if (iteration < i * 2)
		return (create_trgb(100, iteration, iteration, iteration));
	if (iteration < i * 3)
		b = 255;
	else if (iteration < i * 4)
		gg = 255;
	else if (iteration < i * 5)
		return (create_trgb(100, 255, 255, b));
	else if (iteration < i * 6)
		return (create_trgb(100, 255, 127, b));
	else if (iteration < i * 7)
		r = 255;
	return (create_trgb(100, r, gg, b));
}
