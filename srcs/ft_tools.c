/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:20:06 by nflan             #+#    #+#             */
/*   Updated: 2022/04/07 10:49:31 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_free_all(t_all *g, int out)
{
	if (g->setup)
		free(g->setup);
	if (g)
		free(g);
	g = NULL;
	exit (out);
}

char	*ft_strlower(char *str)
{
	int	i;

	i = -1;
	if (str)
		while (str[++i])
			str[i] = ft_tolower(str[i]);
	return (str);
}

void	ft_init_window(t_all *g)
{
	g->setup = NULL;
	g->setup = mlx_init();
	if (!g->setup)
	{
		ft_putstr_fd("Mlx init error\n", 2);
		ft_destroy_win(g, 1);
	}
	g->window = NULL;
	g->window = mlx_new_window(g->setup, g->width, g->height, "Fract'ol");
	if (!g->window)
	{
		ft_putstr_fd("Window error\n", 2);
		ft_destroy_win(g, 1);
	}
}

t_all	*ft_init_all(char **av)
{
	t_all	*g;

	g = NULL;
	g = ft_calloc(sizeof(t_all), 1);
	if (!g)
	{
		ft_putstr_fd("Initialisation issue\n", 2);
		exit (1);
	}
	g->width = ft_atoi(av[2]);
	g->height = ft_atoi(av[3]);
	ft_init_window(g);
	if (!g->setup || !g->window)
		ft_free_all(g, 1);
	g->av = av;
	g->julia = 0;
	if (av[5])
		g->julia = ft_atoi(av[5]);
	ft_init_color(g);
	if (!ft_strncmp(g->av[1], "julia", 6))
		ft_init_julia(g, g->julia);
	else
		ft_init_mandelbrot(g);
	return (g);
}
