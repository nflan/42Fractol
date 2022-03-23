/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/03/23 19:43:21 by nflan            ###   ########.fr       */
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

t_all	*ft_init_all(int ac, char **av)
{
	t_all	*g;

	g = NULL;
	g = ft_calloc(sizeof(t_all), 1);
	if (!g)
		perror("initialisation issue");
	g->width = ft_atoi(av[2]);
	g->height = ft_atoi(av[3]);
	g->setup = NULL;
	g->setup = mlx_init();
	if (!g->setup)
		perror("mlx init error");
	g->window = NULL;
	g->window = mlx_new_window(g->setup, g->width, g->height, av[1]);
	if (!g->window)
		perror("window error");
	if (!g || !g->setup || !g->window)
		return (NULL);
	g->av = av;
	g->ac = ac;
	ft_init_color(g);
	if (!ft_strncmp(g->av[1], "julia", 6))
	{
		g->zoom = 1;
		g->max = 300;
		g->fractal = 2;
	}
	else
	{
		g->zoom = 0;
		g->max = 50;
		g->fractal = 1;
	}
	return (g);
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

int	ft_parse(int ac, char **av)
{
	int	i;

	i = 0;
	if (!ft_strncmp(av[2], "max", 4))
		av[2] = "2560";
	if (!ft_strncmp(av[3], "max", 4))
		av[3] = "1355";
	if (!ft_strncmp(av[1], "color", 6))
		ft_man_color();
	if (!av[2] || ft_atoi(av[2]) < 100 || ft_atoi(av[2]) > 2560)
		i += ft_putstr_fd("Le 2eme arg doit etre un int inferieur a 2560\n", 2);
	if (!av[3] || ft_atoi(av[3]) < 100 || ft_atoi(av[3])> 1355)
		i += ft_putstr_fd("Le 3eme arg doit etre un int inferieur a 1355\n", 2);
	av[1] = ft_strlower(av[1]);
	if (ft_strncmp(av[1], "julia", 6) && ft_strncmp(av[1], "mandelbrot", 11))
		i += ft_putstr_fd("L'argument 1 est Julia ou Mandelbrot\n", 2);
	if (ac < 4 || ac > 5 || i)
	{
		i += ft_putstr_fd("La fonction s'execute comme suit :\nav[1] = nom de la fractale\nav[2] = width (100 <= int <= 2560)\nav[3] = height (100 <= int <= 1355)\nav[4] = color (0 <= int <= 255) (vous pouvez executer la commande \"./fractor color\" pour plus d'informations).\n", 2);
		exit (0);
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_area	ft_init_area_mandelbrot(t_all *g)
{
	t_area	area;

	area.w = g->width;
	area.h = g->height;
	while ((double)area.w / (double)area.h != 1.125)
	{
		if ((double)area.w / (double)area.h > 1.125)
			area.w--;
		if ((double)area.w / (double)area.h < 1.125)
			area.h--;
	}
//	printf("w = %d && h = %d\n", area.w, area.h);
	area.x1 = -2.1 + g->zoom;
	area.x2 = 0.6 - g->zoom;
	area.y1 = -1.2 + g->zoom;
	area.y2 = 1.2 - g->zoom;
	area.image_x = area.w;
	area.image_y = area.h;
	area.zoom_x = area.image_x / (area.x2 - area.x1);// + g->zoom;
	area.zoom_y = area.image_y / (area.y2 - area.y1);// + g->zoom;
	return (area);
}

t_area	ft_init_area_julia(t_all *g)
{
	t_area	area;

	area.w = g->width;
	area.h = g->height;
	while ((double)area.w / (double)area.h != 1.33)
	{
		if ((double)area.w / (double)area.h > 1.33)
			area.w--;
		if ((double)area.w / (double)area.h < 1.33)
			area.h--;
	}
//	printf("w = %d && h = %d\n", area.w, area.h);
	area.x1 = -2.1 + g->zoom;
	area.x2 = 0.6 - g->zoom;
	area.y1 = -1.2 + g->zoom;
	area.y2 = 1.2 - g->zoom;
	area.image_x = area.w;
	area.image_y = area.h;
	area.zoom_x = area.image_x / (area.x2 - area.x1);// + g->zoom;
	area.zoom_y = area.image_y / (area.y2 - area.y1);// + g->zoom;
	return (area);
}

int	ft_julia(t_all *g, t_data img)
{
	t_complex	c;
	t_complex	z;
	int			x;
	int			y;
	int			iteration;
	t_area		area;

	area = ft_init_area_julia(g);
	y = 0;
	g->fractal = 2;
//	printf("row = %d\n", row);
//	printf("area.image_x = %f\n", area.image_x);
//	printf("area.image_y = %f\n", area.image_y);
	c.re = -0.7;
	c.im = 0.27015;
	while (y++ < area.image_y)
	{
		x = 0;
		while (x++ < area.image_x)
		{
			z.re = 1.5 * (x - area.image_x / 2) / (0.5 * g->zoom * area.image_x);
			z.im = (y - area.image_y / 2) / (0.5 * g->zoom * area.image_y);
			iteration = 0;
			while (z.re * z.re + z.im * z.im <= 4 && iteration < g->max)
			{
				z.tmpre = z.re;
				z.re = z.tmpre * z.tmpre - z.im * z.im + c.re;
				z.im = z.im * z.tmpre + z.im * z.tmpre + c.im;
				iteration++;
			}
			if (iteration == g->max)
				my_mlx_pixel_put(&img, x + ((g->width - area.w) / 2), y + ((g->height - area.h) / 2), create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&img, x + ((g->width - area.w) / 2), y + ((g->height - area.h) / 2), ft_deg(iteration, g, 100, g->color));
		}
	}
//	printf("C'est print\n");
	return (0);
}

int	ft_mandelbrot(t_all *g, t_data img) // zoom
{
	t_complex	c;
	t_complex	z;
	int			row;
	int			col;
	int			iteration;
	t_area		area;

	area = ft_init_area_mandelbrot(g);
	row = 0;
	g->fractal = 1;
//	printf("row = %d\n", row);
//	printf("area.image_x = %f\n", area.image_x);
//	printf("area.image_y = %f\n", area.image_y);
	while (row++ < area.image_x)
	{
		col = 0;
		while (col++ < area.image_y)
		{
			c.re = row / area.zoom_x + area.x1;
			c.im = col / area.zoom_y + area.y1;
			z.im = 0;
			z.re = 0;
			iteration = 0;
			while (z.re * z.re + z.im * z.im < 4 && iteration < g->max)
			{
				z.tmpre = z.re * z.re - z.im * z.im + c.re;
				z.im = z.im * z.re + z.im * z.re + c.im;
				z.re = z.tmpre;
				iteration++;
			}
			if (iteration == g->max)
				my_mlx_pixel_put(&img, row + ((g->width - area.w) / 2), col + ((g->height - area.h) / 2), create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&img, row + ((g->width - area.w) / 2), col + ((g->height - area.h) / 2), ft_deg(iteration, g, 100, g->color));
		}
	}
//	printf("C'est print\n");
	return (0);
}

int	ft_limits(int key, t_all *g)
{
	if (!ft_strncmp(g->av[1], "mandelbrot", 11))
		if (g->zoom >= 1.1 && key == 4)
			return (1);
	if (!ft_strncmp(g->av[1], "julia", 6))
		if (g->zoom <= 0.2 && key == 5)
			return (1);
	return (0);
}

int	ft_zoom(int key, t_all *g)
{
	printf("g->zoom = %f\n", g->zoom);
	if (key != 114)
		if (ft_limits(key, g))
			return (1);
	if (key == 4)
		g->zoom += 0.1;
	else if (key == 5)
		g->zoom -= 0.1;
	else if (key == 114)
	{
		if (!ft_strncmp(g->av[1], "julia", 6))
		{
			g->zoom = 1;
			g->max = 300;
		}
		else
		{
			g->zoom = 0;
			g->max = 50;
		}
	}
	ft_print_new(g);
	return (0);
}

int	ft_mouse(int keycode, int x, int y, t_all *g)
{
	(void)x;
	(void)y;
//	printf("x = %d && y = %d\n", x, y);
	if (keycode == 4 || keycode == 5)
		return (ft_zoom(keycode, g));
	return (0);
}

int	ft_destroy_win(t_all *g)
{
	mlx_destroy_image(g->setup, g->img.img);
	mlx_clear_window(g->setup, g->window);
	mlx_destroy_window(g->setup, g->window);
	mlx_destroy_display(g->setup);
	ft_free_all(g);
	exit (0);
}

int	ft_net(int key, t_all *g)
{
	if (key == 65453)
		g->max -= 5;
	else if (key == 65451)
		g->max += 5;
	else if (key == 65469)
	{
		if (g->fractal == 1)
			g->max = 50;
		else
			g->max = 300;
	}
	if (g->max <= 0)
	{
		g->max = 5;
		return (0);
	}
	ft_print_new(g);
	return (0);
}

int	ft_input(int keycode, t_all *g)
{
	int i;

	i = 100;
//	printf("keycode = %d\n", keycode);
	if (keycode == 65361 || keycode == 65363)
		ft_change_color(keycode, g);
	if (keycode == 98)
		while (i-- > 0)
			ft_change_color(65363, g);
	if (keycode == 106 || keycode == 109)
	{
		if (keycode == 106 && ft_strncmp(g->av[1], "julia", 6))
			g->av[1] = "julia";
		else if (keycode == 109 && ft_strncmp(g->av[1], "mandelbrot", 11))
			g->av[1] = "mandelbrot";
		else
			return (0);
		ft_zoom(114, g);
	}
	if (keycode == 113 || keycode == 65307)
		ft_destroy_win(g);
	if (keycode == 114)
		ft_zoom(keycode, g);
	if (keycode == 65453 || keycode == 65451 || keycode == 65469)
		ft_net(keycode, g);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	*g;

	ft_parse(ac, av);
	g = ft_init_all(ac, av);
	if (!g)
		return (1);
	g->img.img = mlx_new_image(g->setup, g->width, g->height);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel, &g->img.line_length, &g->img.endian);
	if (!ft_strncmp(av[1], "julia", 6))
		ft_julia(g, g->img);
	else
		ft_mandelbrot(g, g->img);
	mlx_put_image_to_window(g->setup, g->window, g->img.img, 0, 0);
	mlx_hook(g->window, 2, 1L << 0, ft_input, g);
	mlx_hook(g->window, 4, 1L << 2, ft_mouse, g);
	mlx_hook(g->window, 17, 0, ft_destroy_win, g);
	mlx_loop(g->setup);
	return (0);
}
