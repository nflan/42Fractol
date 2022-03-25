/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:20:06 by nflan             #+#    #+#             */
/*   Updated: 2022/03/25 17:25:30 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void	ft_free_all(t_all *g)
{
	if (g->setup)
		free(g->setup);
	if (g)
		free(g);
	g = NULL;
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
		ft_putstr_fd("mlx init error\n", 2);
		ft_destroy_win(g);
	}
	g->window = NULL;
	g->window = mlx_new_window(g->setup, g->width, g->height, "Fract'ol");
	if (!g->window)
	{
		ft_putstr_fd("window error\n", 2);
		ft_destroy_win(g);
	}
}

t_all	*ft_init_all(char **av)
{
	t_all	*g;

	g = NULL;
	g = ft_calloc(sizeof(t_all), 1);
	if (!g)
	{
		ft_putstr_fd("initialisation issue\n", 2);
		return (NULL);
	}
	g->width = ft_atoi(av[2]);
	g->height = ft_atoi(av[3]);
	ft_init_window(g);
	if (!g->setup || !g->window)
		return (NULL);
	g->av = av;
	ft_init_color(g);
	g->julia = 0;
	if (!ft_strncmp(g->av[1], "julia", 6))
		ft_init_julia(g, ft_atoi(av[5]));
	else
		ft_init_mandelbrot(g);
	return (g);
}

int	ft_parse(int ac, char **av, int i)
{
	if (!ft_strncmp(av[1], "color", 6))
		return (ft_man_color());
	if (!ft_strncmp(av[2], "max", 4))
		av[2] = "2560";
	if (!ft_strncmp(av[3], "max", 4))
		av[3] = "1355";
	if (!av[2] || ft_atoi(av[2]) < 150 || ft_atoi(av[2]) > 2560)
		i += ft_putstr_fd("Le 2eme arg doit etre un int > 150 et < 2560\n", 2);
	if (!av[3] || ft_atoi(av[3]) < 150 || ft_atoi(av[3]) > 1355)
		i += ft_putstr_fd("Le 3eme arg doit etre un int > 150 et < 1355\n", 2);
	av[1] = ft_strlower(av[1]);
	if (ft_strncmp(av[1], "julia", 6) && ft_strncmp(av[1], "mandelbrot", 11))
		i += ft_putstr_fd("L'argument 1 est Julia ou Mandelbrot\n", 2);
	if (av[5] && (ft_atoi(av[5]) < 0 || ft_atoi(av[5]) > 9))
		i += ft_putstr_fd("Les ensembles de Julia traites vont de 0 a 9\n", 2);
	if (ac < 4 || ac > 6 || i)
	{
		i += ft_putstr_fd("La fonction s'execute comme suit :\
				\nav[1] = nom de la fractale\nav[2] = width (150 <= int <= 2560)\
				\nav[3] = height (150 <= int <= 1355)\
				\nav[4] = color (0 <= int <= 255) (vous pouvez executer\
la commande \"./fractor color\" pour plus d'informations).\
				\nav[5] = ensemble de Julia (1 par defaut)\n", 2);
		exit (1);
	}
	return (0);
}
