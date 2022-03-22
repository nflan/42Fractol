/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/03/22 18:02:19 by nflan            ###   ########.fr       */
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
	g->zoom = 0;
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
//	printf("keycode = %d\n", keycode);
	if (keycode == 65361 || keycode == 65363)
		ft_change_color(keycode, g);
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

void	ft_julia(t_all *g, t_data img)
{
	(void)g;
	(void)img;
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
	area.x1 = -2.1;
	area.x2 = 0.6;
	area.y1 = -1.2;
	area.y2 = 1.2;
	area.image_x = area.w;
	area.image_y = area.h;
	area.zoom_x = area.image_x / (area.x2 - area.x1) + g->zoom;
	area.zoom_y = area.image_y / (area.y2 - area.y1) + g->zoom;
	return (area);
}

int	ft_mandelbrot(t_all *g, t_data img) // zoom
{
	t_complex	c;
	double		x;
	double		y;
	double		x_new;
	int			row;
	int			col;
	int			iteration;
	int			max = 50;
	t_area		area;

	area = ft_init_area_mandelbrot(g);
	row = 0;
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
			x = 0;
			y = 0;
			iteration = 0;
			while (x * x + y * y < 4 && iteration < max)
			{
				x_new = x * x - y * y + c.re;
				y = 2 * y * x + c.im;
				x = x_new;
				iteration++;
			}
			if (iteration == max)
				my_mlx_pixel_put(&img, row + ((g->width - area.w) / 2), col + ((g->height - area.h) / 2), ft_deg(iteration, max, 100, 0));
			else
				my_mlx_pixel_put(&img, row + ((g->width - area.w) / 2), col + ((g->height - area.h) / 2), ft_deg(iteration, max, 100, g->color));
		}
	}
	mlx_put_image_to_window(g->setup, g->window, img.img, 0, 0);
	printf("C'est print\n");
	return (0);
}

int	ft_zoom_in(t_all *g)
{
	mlx_destroy_image(g->setup, g->img.img);
	mlx_clear_window(g->setup, g->window);
	g->zoom = 100;
	g->img.img = mlx_new_image(g->setup, g->width, g->height);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel, &g->img.line_length, &g->img.endian);
	return (ft_mandelbrot(g, g->img));
}

int	ft_zoom_out(t_all *g)
{
	mlx_destroy_image(g->setup, g->img.img);
	mlx_clear_window(g->setup, g->window);
	g->zoom -= 100;
	g->img.img = mlx_new_image(g->setup, g->width, g->height);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel, &g->img.line_length, &g->img.endian);
	return (ft_mandelbrot(g, g->img));
}

int	ft_mouse(int keycode, t_all *g)
{
	if (keycode == 4)
		return (ft_zoom_in(g));
	else
		return (ft_zoom_out(g));
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
	if (!ft_strncmp(av[1], "julia", 6))
		ft_julia(g, g->img);
	else
		ft_mandelbrot(g, g->img);
	mlx_hook(g->window, 2, 1L << 0, ft_input, g);
	mlx_hook(g->window, 17, 0, ft_destroy_win, g);
	mlx_mouse_hook(g->window, ft_mouse, g);
	mlx_loop(g->setup);
	return (0);
}
