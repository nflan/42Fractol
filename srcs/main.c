/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/03/21 18:53:20 by nflan            ###   ########.fr       */
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
	return (g);
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

int	ft_input(int keycode, t_all *g)
{
	//printf("keycode = %d\n", keycode);
	if (keycode == 113 || keycode == 65307)
		ft_destroy_win(g);
	return (0);
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
	if (!av[2] || (av[2] && ft_atoi(av[2]) < 960))
		i += ft_putstr_fd("Le 2eme arg doit etre un int superieur a 980\n", 1);
	if (!av[3] || (av[3] && ft_atoi(av[3]) < 540))
		i += ft_putstr_fd("Le 3eme arg doit etre un int superieur a 540\n", 1);
	av[1] = ft_strlower(av[1]);
	if (ft_strncmp(av[1], "julia", 6) && ft_strncmp(av[1], "mandelbrot", 11))
		i += ft_putstr_fd("L'argument 1 est Julia ou Mandelbrot\n", 1);
	if (ac != 4 || i)
	{
		i += ft_putstr_fd("La fonction s'execute comme suit :\nav[1] = nom de la fractale\nav[2] = width (int > 0)\nav[3] = height (int > 0)\n", 1);
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
/*	while (x > 0 && y > 0)
	{
		x--;
		y--;
	}
*/}

void	ft_julia(t_all *g, t_data img)
{
	int i = 5;
	while (i > 1.0)
	{
		my_mlx_pixel_put(&img, g->width / i, g->height / i, create_trgb(100, 255, 150, 200));
		i -= 0.5;
	}
	mlx_put_image_to_window(g->setup, g->window, img.img, 0, 0);
}

/*void	ft_mandelbrot(t_all *g, t_data img)
{
	t_color		rgb;
	int			A, B, i;
	double		a, b, x, y, t, n;
	
	n = g->width / 2;
	rgb.r = 255;
	rgb.g = 255;
	rgb.b = 255;
	A = g->width / 2;
	B = g->height / 2;
	while (B++ <= 4 * n + (g->height / 2))
	{
		b = 2 - (B / n);
		while (A++ <= 4 * n + (g->width / 2))
		{
			a = -2 + (A / n);
			printf("a = %f\n", a);
			x = 0;
			y = 0;
			i = 1;
			while (i++ <= g->width / 2)
			{
				t = x;
				x = (x * x) - (y * y) + a;
				y = (2 * t * y) + b;
				if ((x * x) + (y * y) > 4)
				{
					printf("i = %d\n", i);
					break;
				}
			}
			if (i > g->width / 2)
			{
				printf("ok\n");
				my_mlx_pixel_put(&img, A, B, create_trgb(100, rgb.r, rgb.g, rgb.b));
			}
		}
	}
	mlx_put_image_to_window(g->setup, g->window, img.img, 0, 0);
}*/

void	ft_mandelbrot(t_all *g, t_data img)
{
	int	row = 0;
	int	col;
	t_complex	c;
	double	x;
	double	y;
	int		iteration;
	double	x_new;
	int		max = 1920;

	while (row++ < g->height)
	{
		col = 0;
		while (col++ < g->width)
		{
			c.re = (col - g->width / 2.0) * 4.0 / g->width;
			c.im = (row - g->height / 2.0) * 4.0 / g->width;
			x = 0;
			y = 0;
			iteration = 0;
			while (x * x + y * y <= 4 && iteration < max)
			{
				x_new = x * x - y * y + c.re;
				y = 2 * x * y + c.im;
				x = x_new;
				iteration++;
			}
			printf("iteration = %d\n", iteration);
			if (iteration < max && col < g->width && iteration > 6)
				my_mlx_pixel_put(&img, col, row, create_trgb(100, iteration, iteration / 3, iteration / 2));
			else if (iteration < 3)
			{
				my_mlx_pixel_put(&img, col, row, create_trgb(iteration * 10, 0, 0, 255));
			}
			else if (iteration > 2 && iteration < 5)
			{
				my_mlx_pixel_put(&img, col, row, create_trgb(iteration * 10, 255, 255, 255));
			}
			else if (iteration > 4 && iteration < 7)
			{
				my_mlx_pixel_put(&img, col, row, create_trgb(iteration * 10, 255, 0, 0));
			}
			else
				my_mlx_pixel_put(&img, col, row, create_trgb(100, 0, 0, 0));
		}
	}
	mlx_put_image_to_window(g->setup, g->window, img.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_all	*g;
	t_data	img;

	ft_parse(ac, av);
	g = ft_init_all(ac, av);
	if (!g)
		return (1);
	img.img = mlx_new_image(g->setup, g->width, g->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	g->img = img;
//	if (!ft_strncmp(av[1], "julia", 6))
//		ft_julia(g, img);
//	else
//		ft_mandelbrot(g, img);
	mlx_hook(g->window, 2, 1L << 0, ft_input, g);
	mlx_hook(g->window, 17, 0, ft_destroy_win, g);
	mlx_loop(g->setup);
	return (0);
}
