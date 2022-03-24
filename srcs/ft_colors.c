/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:31:25 by nflan             #+#    #+#             */
/*   Updated: 2022/03/24 17:55:19 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_man_color(void)
{
	ft_printf("Voici les couleurs possibles a donner en 4eme argument si besoin :\n\n");
	ft_printf("Noir\t= 0\n");
	ft_printf("Rouge\t= 1\n");
	ft_printf("Vert\t= 2\n");
	ft_printf("Bleu\t= 3\n");
	ft_printf("Jaune\t= 12\n");
	ft_printf("Rose\t= 13\n");
	ft_printf("Turquoise\t= 23\n");
	ft_printf("Rainbow\t= 50\n");
	ft_printf("Rainbow psyche\t= 51\n");
	ft_printf("Un peu de tout\t= 123\n");
	ft_printf("Rouge psyche\t= 151\n");
	ft_printf("Blanc\t= 255\n");
	exit (0);
}

void	ft_init_color(t_all *g)
{
	int	i;

	i = 0;
	g->pal[0] = 0;
	g->pal[1] = 1;
	g->pal[2] = 2;
	g->pal[3] = 3;
	g->pal[4] = 12;
	g->pal[5] = 13;
	g->pal[6] = 23;
	g->pal[7] = 50;
	g->pal[8] = 51;
	g->pal[9] = 123;
	g->pal[10] = 151;
	g->pal[11] = 255;
	if (g->av[4])
	{
		g->color = atoi(g->av[4]);
		while (i >= 0 && i <= 10)
			if (g->pal[i++] == g->color)
				i = -1;
		if (i != -1)
			g->color = 255;
	}
}

int	ft_print_new(t_all *g)
{
	g->curr.img = mlx_new_image(g->setup, g->width, g->height);
	g->curr.addr = mlx_get_data_addr(g->curr.img, &g->curr.bits_per_pixel, &g->curr.line_length, &g->curr.endian);
	if (g->fractal == 1)
		ft_mandelbrot(g, g->curr);
	else
		ft_julia(g, g->curr);
	mlx_destroy_image(g->setup, g->img.img);
	mlx_clear_window(g->setup, g->window);
	g->img = g->curr;
	mlx_put_image_to_window(g->setup, g->window, g->img.img, 0, 0);
	return (0);
}

int	ft_change_color(int key, t_all *g)
{
	int	i;

	i = 0;
	while (g->pal[i] != g->color && i <= 11)
		i++;
	if (key == 65361)
	{
		if (i == 0)
			g->color = g->pal[11];
		else
			g->color = g->pal[i - 1];
	}
	else if (key == 65363)
	{
		if (i == 11)
			g->color = g->pal[0];
		else
			g->color = g->pal[i + 1];
	}
	ft_print_new(g);
	return (0);
}

int	ft_rgb_psy(t_all *g, int iteration)
{
	int	r;
	int	gg;
	int	b;
	int	i;

	i = g->max / 7;
	if (iteration < i * 2)
		return (create_trgb(100, iteration, iteration, iteration));
	if (iteration < i * 3)
	{
		r = 0;
		gg = 0;
		b = iteration * i;
	}
	else if (iteration < i * 4)
	{
		r = 0;
		gg = iteration * i;
		b = 0;
	}
	else if (iteration < i * 5)
	{
		r = iteration * i;
		gg = iteration * i;
		b = 0;
	}
	else if (iteration < i * 6)
	{
		r = iteration * i;
		gg = iteration * i / 2;
		b = 0;
	}
	else if (iteration < i * 7)
	{
		r =  iteration * i;
		gg = 0;
		b = 0;
	}
	else
	{
		r = 0;
		gg = 0;
		b = 0;
	}
	return (create_trgb(100, r, gg, b));
}

int	ft_red_psy(t_all *g, int iteration)
{
	int	r;
	int	gg;
	int	b;
	int	i;

	i = g->max / 7;
	if (iteration < i * 2)
		return (create_trgb(100, iteration, iteration, iteration));
	if (iteration < i * 3)
	{
		r = 0;
		gg = 0;
		b = 255 - iteration * i;
	}
	else if (iteration < i * 4)
	{
		r = 0;
		gg = 255 - iteration * i;
		b = 0;
	}
	else if (iteration < i * 5)
	{
		r = 255 - iteration * i;
		gg = 255 - iteration * i;
		b = 0;
	}
	else if (iteration < i * 6)
	{
		r = 255 - iteration * i;
		gg = 255 - iteration * i / 2;
		b = 0;
	}
	else if (iteration < i * 7)
	{
		r = 255 - iteration * i;
		gg = 0;
		b = 0;
	}
	else
	{
		r = 0;
		gg = 0;
		b = 0;
	}
	return (create_trgb(100, r, gg, b));
}

int	ft_rgb(t_all *g, int iteration)
{
	int	r;
	int	gg;
	int	b;
	int	i;

	r = 255;
	gg = 255;
	b = 255;
	i = g->max / 7;
	if (iteration < i * 2)
		return (create_trgb(100, iteration, iteration, iteration));
	if (iteration < i * 3)
	{
		r = 0;
		gg = 0;
		b = 255;
	}
	else if (iteration < i * 4)
	{
		r = 0;
		gg = 255;
		b = 0;
	}
	else if (iteration < i * 5)
	{
		r = 255;
		gg = 255;
		b = 0;
	}
	else if (iteration < i * 6)
	{
		r = 255;
		gg = 127;
		b = 0;
	}
	else if (iteration < i * 7)
	{
		r = 255;
		gg = 0;
		b = 0;
	}
	else
	{
		r = 0;
		gg = 0;
		b = 0;
	}
	return (create_trgb(100, r, gg, b));
}

int	ft_deg(int iteration, t_all *g, int t, int i)
{
	int	color;

	color = iteration * 255 / g->max;
	if (i == 123)
	{
		if (iteration > 42)
			i = 3;
		else if (iteration > 35)
			i = 2;
		else if (iteration > 28)
			i = 1;
		else if (iteration > 5)
		{
			color = iteration * 100 / 25 * iteration;
			i = 100;
		}
		else
		{
			color = iteration * 255 / g->max * 10;
			i = 3;
		}
	}
	if (i == 0 && color > 75)
		return (create_trgb(t, 255 - color, 255 - color, 255 - color));
	if (i == 1)
		return (create_trgb(t, color, 0, 0));
	if (i == 2)
		return (create_trgb(t, 0, color, 0));
	if (i == 3)
		return (create_trgb(t, 0, 0, color));
	if (i == 12)
		return (create_trgb(t, color, color, 0));
	if (i == 13)
		return (create_trgb(t, color, 0, color));
	if (i == 23)
		return (create_trgb(t, 0, color, color));
	if (i == 50)
		return (ft_rgb(g, iteration));
	if (i == 51)
		return (ft_rgb_psy(g, iteration));
	if (i == 151)
		return (ft_red_psy(g, iteration));
	return (create_trgb(t, color, color, color));
}
