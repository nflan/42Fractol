/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:31:25 by nflan             #+#    #+#             */
/*   Updated: 2022/04/04 17:03:16 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_man_color(void)
{
	ft_printf("Voici les couleurs possibles a donner\
 en 4eme argument si besoin :\n\n");
	ft_printf("Noir\t\t= 0\n");
	ft_printf("Rouge\t\t= 1\n");
	ft_printf("Vert\t\t= 2\n");
	ft_printf("Bleu\t\t= 3\n");
	ft_printf("Jaune\t\t= 12\n");
	ft_printf("Rose\t\t= 13\n");
	ft_printf("Turquoise\t= 23\n");
	ft_printf("Rainbow\t\t= 50\n");
	ft_printf("Rainbow psyche\t= 51\n");
	ft_printf("Un peu de tout\t= 123\n");
	ft_printf("Rouge psyche\t= 151\n");
	ft_printf("Blanc\t\t= 255\n");
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

int	ft_change_color(int key, t_all *g)
{
	int	i;

	i = 0;
	while (g->pal[i] != g->color && i <= 11)
		i++;
	if (key == 65430)
	{
		if (i == 0)
			g->color = g->pal[11];
		else
			g->color = g->pal[i - 1];
	}
	else if (key == 65432)
	{
		if (i == 11)
			g->color = g->pal[0];
		else
			g->color = g->pal[i + 1];
	}
	ft_print_new(g);
	return (0);
}

int	ft_deg2(int iteration, t_all *g, int i, int color)
{
	if (i == 0 && color > 75)
		return (create_trgb(100, 255 - color, 255 - color, 255 - color));
	if (i == 1)
		return (create_trgb(100, color, 0, 0));
	if (i == 2)
		return (create_trgb(100, 0, color, 0));
	if (i == 3)
		return (create_trgb(100, 0, 0, color));
	if (i == 12)
		return (create_trgb(100, color, color, 0));
	if (i == 13)
		return (create_trgb(100, color, 0, color));
	if (i == 23)
		return (create_trgb(100, 0, color, color));
	if (i == 50)
		return (ft_rgb(g, iteration));
	if (i == 51)
		return (ft_rgb_psy(g, iteration));
	if (i == 151)
		return (ft_red_psy(g, iteration));
	return (create_trgb(100, color, color, color));
}

int	ft_deg(int iteration, t_all *g, int i)
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
	return (ft_deg2(iteration, g, i, color));
}
