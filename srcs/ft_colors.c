/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:31:25 by nflan             #+#    #+#             */
/*   Updated: 2022/03/23 19:15:04 by nflan            ###   ########.fr       */
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
	ft_printf("ok\t= 50\n");
	ft_printf("Un peu de tout\t= 123\n");
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
	g->pal[8] = 123;
	g->pal[9] = 255;
	if (g->av[4])
	{
		g->color = atoi(g->av[4]);
		while (i >= 0 && i <= 9)
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
	if (!ft_strncmp(g->av[1], "mandelbrot", 11))
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
	while (g->pal[i] != g->color && i >= 0 && i <= 9)
		i++;
	if (key == 65361)
	{
		if (i == 0)
			g->color = g->pal[9];
		else
			g->color = g->pal[i - 1];
	}
	else if (key == 65363)
	{
		if (i == 9)
			g->color = g->pal[0];
		else
			g->color = g->pal[i + 1];
	}
	ft_print_new(g);
	return (0);
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
	if (i == 50 && !strncmp(g->av[1], "julia", 6))
		return (create_trgb(t, iteration % 256, 255, 255 * (iteration < g->max)));
	return (create_trgb(t, color, color, color));
}
