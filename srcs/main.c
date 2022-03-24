/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/03/24 17:55:41 by nflan            ###   ########.fr       */
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

void	ft_init_julia(t_all *g, int e)
{
	g->julia = 1;
	g->zoom = 1;
	if (e == 1 || e == 49)
	{
		g->c.re = -0.7;
		g->c.im = 0.27015;
		g->max = 300;
	}
	else if (e == 2 || e == 50)
	{
		g->c.re = -1.25;
		g->c.im = 0;
		g->zoom = 0.8;
		g->max = 50;
		g->julia = 2;
	}
	else if (e == 3 || e == 51)
	{
		g->c.re = -0.56;
		g->c.im = 0.645;
		g->julia = 3;
		g->max = 100;
	}
	g->fractal = 2;
}

void	ft_init_mandelbrot(t_all *g)
{
	if (!g->av[5])
		g->julia = 1;
	else if (g->av[5][0] == '1' || g->av[5][0] == '2')
		g->julia = ft_atoi(g->av[5]);
	g->zoom = 0;
	g->max = 50;
	g->fractal = 1;
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
		ft_init_julia(g, ft_atoi(av[5]));
	else
		ft_init_mandelbrot(g);
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
	if (av[5] && (ft_atoi(av[5]) < 1 || ft_atoi(av[5]) > 3))
		i += ft_putstr_fd("Les ensembles de Julia traites vont de 1 a 3\n", 2);
	if (ac < 4 || ac > 6 || i)
	{
		i += ft_putstr_fd("La fonction s'execute comme suit :\nav[1] = nom de la fractale\nav[2] = width (100 <= int <= 2560)\nav[3] = height (100 <= int <= 1355)\nav[4] = color (0 <= int <= 255) (vous pouvez executer la commande \"./fractor color\" pour plus d'informations).\nav[5] = ensemble de Julia (1 par defaut)\n", 2);
		exit (0);
	}
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*int	get_color(int trgb, int c)
  {
  if (c == 't')
  return ((trgb >> 24) & 0xFF);
  else if (c == 'r')
  return ((trgb >> 16) & 0xFF);
  else if (c == 'g')
  return ((trgb >> 8) & 0xFF);
  else if (c == 'b')
  return (trgb & 0xFF);
  return (0);
  }*/

void	my_mlx_pixel_put(t_data *data, t_all *g, t_area area, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = g->x + ((g->width - area.w) / 2);
	y = g->y + ((g->height - area.h) / 2);
	if (g->x <= area.w && g->y <= area.h && x > 0 && y > 0)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

/*void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}*/

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
	area.image_x = area.w;
	area.image_y = area.h;
	area.zoom_x = 0.5 * g->zoom * area.image_x;
	area.zoom_y = 0.5 * g->zoom * area.image_y;
	return (area);
}

int	ft_julia(t_all *g, t_data img)
{
	t_complex	z;
	int			iteration;
	t_area		area;

	area = ft_init_area_julia(g);
	g->y = 0;
	g->fractal = 2;
	//	printf("row = %d\n", row);
	//	printf("area.image_x = %f\n", area.image_x);
	//	printf("area.image_y = %f\n", area.image_y);
	while (g->y++ < area.image_y)
	{
		g->x = 0;
		while (g->x++ < area.image_x)
		{
			z.re = 1.5 * (g->x - area.image_x / 2) / area.zoom_x;
			z.im = (g->y - area.image_y / 2) / area.zoom_y;
			iteration = 0;
			while (z.re * z.re + z.im * z.im <= 4 && iteration < g->max)
			{
				z.tmpre = z.re;
				z.re = z.tmpre * z.tmpre - z.im * z.im + g->c.re;
				z.im = z.im * z.tmpre + z.im * z.tmpre + g->c.im;
				iteration++;
			}
			if (iteration == g->max)
				my_mlx_pixel_put(&img, g, area, create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&img, g, area, ft_deg(iteration, g, 100, g->color));
		}
	}
	//	printf("C'est print\n");
	return (0);
}

int	ft_mandelbrot(t_all *g, t_data img) // zoom
{
	t_complex	z;
	int			iteration;
	t_area		area;

	area = ft_init_area_mandelbrot(g);
	g->x = 0;
	g->fractal = 1;
	//	printf("row = %d\n", row);
	//	printf("area.image_x = %f\n", area.image_x);
	//	printf("area.image_y = %f\n", area.image_y);
	while (g->x++ < area.image_x)
	{
		g->y = 0;
		while (g->y++ < area.image_y)
		{
			g->c.re = g->x / area.zoom_x + area.x1;
			g->c.im = g->y / area.zoom_y + area.y1;
		//	printf("g->c.re = %f && g->c.im = %f\n", g->c.re, g->c.im);
			z.im = 0;
			z.re = 0;
			iteration = 0;
			while (z.re * z.re + z.im * z.im < 4 && iteration < g->max)
			{
				z.tmpre = z.re * z.re - z.im * z.im + g->c.re;
				z.im = z.im * z.re + z.im * z.re + g->c.im;
				z.re = z.tmpre;
		//		printf("z.re = %f && z.im = %f\n", z.re, z.im);
				iteration++;
			}
			if (iteration == g->max)
				my_mlx_pixel_put(&img, g, area, create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&img, g, area, ft_deg(iteration, g, 100, g->color));
		}
	}
	//	printf("C'est print\n");
	return (0);
}

int	ft_limits(int key, t_all *g)
{
	if (g->fractal == 1)
		if (g->zoom >= 1.1 && key == 4)
			return (1);
	if (g->fractal == 2)
		if (g->zoom <= 0.2 && key == 5)
			return (1);
	return (0);
}

int	ft_change(int key, t_all *g)
{
	if (key == 106 && g->fractal != 2)
		ft_init_julia(g, g->julia);
	else if (key == 109 && g->fractal != 1)
		ft_init_mandelbrot(g);
	return (0);
}
int	ft_zoom(int key, t_all *g)
{
	if (key != 114)
		if (ft_limits(key, g))
			return (1);
	if (key == 4)
		g->zoom += 0.1;
	else if (key == 5)
		g->zoom -= 0.1;
	else if (key == 114)
	{
		if (g->fractal == 1)
			g->zoom = 0;
		else if (g->fractal == 2 && g->julia == 1)
			g->zoom = 0.8;
		else
			g->zoom = 1;
	}
	else if (key == 65362 && g->fractal == 2)
	{
		if (g->zoom == 0.3 && g->julia == 2)
			g->zoom = 1;
		else if (g->zoom == 0.3 && g->julia != 2)
			g->zoom = 0.8;
		else
			g->zoom += 10;
	}
	else if (key == 65364 && g->fractal == 2)
	{
		g->zoom -= 10;
		if (g->zoom < 0.3)
			g->zoom = 0.3;
	}
	return (0);
}

int	ft_mouse(int keycode, int x, int y, t_all *g)
{
	(void)x;
	(void)y;
//	printf("x = %d && y = %d\n", x, y);
	if (keycode == 4 || keycode == 5)
		ft_zoom(keycode, g);
	ft_print_new(g);
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
	if (key == 65450)
		g->max += 50;
	else if (key == 65451)
		g->max += 5;
	else if (key == 65453)
		g->max -= 5;
	else if (key == 65455)
		g->max -= 50;
	else if (key == 65469)
	{
		if (g->fractal == 1)
			g->max = 50;
		else if (g->fractal == 2 && g->julia == 1)
			g->max = 300;
		else
			g->max = 100;
	}
	if (g->max <= 0)
	{
		g->max = 5;
		return (0);
	}
	return (0);
}

int	ft_input(int keycode, t_all *g)
{
	int i;

	i = 100;
//	printf("keycode = %d\n", keycode);
	if (keycode == 65361 || keycode == 65363)
		ft_change_color(keycode, g);
	else if (keycode == 98)
		while (i-- > 0)
			ft_change_color(65363, g);
	else if (keycode == 106 || keycode == 109)
		ft_change(keycode, g);
	else if (keycode == 113 || keycode == 65307)
		ft_destroy_win(g);
	else if (keycode == 114 || keycode == 65362 || keycode == 65364)
		ft_zoom(keycode, g);
	else if ((keycode >= 65450 && keycode <= 65455) || keycode == 65469)
		ft_net(keycode, g);
	else if (keycode >= 49 && keycode <= 51 && g->fractal == 2)
		ft_init_julia(g, keycode);
	ft_print_new(g);
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
//	printf("g->fractal = %d\n", g->fractal);
	if (g->fractal == 2)
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
