/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:26:52 by nflan             #+#    #+#             */
/*   Updated: 2022/04/05 13:53:49 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

t_data	ft_init_img(t_all *g)
{
	t_data	img;

	img.img = NULL;
	img.addr = NULL;
	img.img = mlx_new_image(g->setup, g->width, g->height);
	if (!img.img)
		ft_destroy_win(g, 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	if (!img.addr)
	{
		free(img.img);
		img.img = NULL;
		ft_destroy_win(g, 1);
	}
	return (img);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, t_all *g, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = g->x + ((g->width - g->area.w) / 2);
	y = g->y + ((g->height - g->area.h) / 2);
	if (g->x <= g->area.w && g->y <= g->area.h && x > 0 && y > 0 && color != 0)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_destroy_win(t_all *g, int out)
{
	if (out == 309)
		out = 0;
	if (g->window)
	{
		if (g->img.img && g->img.addr)
			mlx_destroy_image(g->setup, g->img.img);
		mlx_clear_window(g->setup, g->window);
		mlx_destroy_window(g->setup, g->window);
	}
	if (g->setup)
		mlx_destroy_display(g->setup);
	ft_free_all(g, out);
	exit (out);
}
