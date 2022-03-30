/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:52:06 by nflan             #+#    #+#             */
/*   Updated: 2022/03/30 11:20:49 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"

typedef struct s_complex
{
	double	re;
	double	im;
	double	tmpre;
}	t_complex;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_area
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	zoom_x;
	double	zoom_y;
	int		w;
	int		h;
}	t_area;

typedef struct s_all
{
	char			**av;
	void			*setup;
	void			*window;
	double			zoom;
	int				pal[12];
	int				julia;
	int				width;
	int				height;
	int				color;
	int				x;
	int				y;
	int				fractal;
	double			posx;
	double			posy;
	double			mousex;
	double			mousey;
	unsigned int	max;
	t_complex		c;
	t_data			img;
	t_data			curr;
	t_area			area;
}	t_all;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

// MAIN

// COLORS
int		ft_man_color(void);
void	ft_init_color(t_all *g);
int		ft_change_color(int key, t_all *g);
int		ft_rgb_psy(t_all *g, int iteration);
int		ft_red_psy(t_all *g, int iteration);
int		ft_rgb(t_all *g, int iteration);
int		ft_deg2(int iteration, t_all *g, int i, int color);
int		ft_deg(int iteration, t_all *g, int i);

// UTILS
int		ft_change(int key, t_all *g);
int		ft_net(int key, t_all *g);
int		ft_mouse(int keycode, int x, int y, t_all *g);
int		ft_input(int keycode, t_all *g);
int		ft_print_new(t_all *g);

// ZOOM
int		ft_zoom_mandelbrot(int key, t_all *g);
int		ft_zoom_julia(int key, t_all *g);
int		ft_zoom(int key, t_all *g);
int		ft_limits(int key, t_all *g);

// TOOLS
void	ft_free_all(t_all *g);
char	*ft_strlower(char *str);
t_all	*ft_init_all(char **av);
int		ft_parse(int ac, char **av, int i);

// WINDOW
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, t_all *g, int color);
int		ft_destroy_win(t_all *g);

// JULIA
void	ft_julia_tool(t_all *g, double re, double im, int max);
void	ft_init_julia(t_all *g, int e);
void	ft_init_zoom_julia(t_all *g, int z);
void	ft_check_julia(t_all *g);
void	ft_julia(t_all *g, t_data img);

// MABNDELBROT
void	ft_init_mandelbrot(t_all *g);
void	ft_init_zoom_mandelbrot(t_all *g, int z);
void	ft_mandelbrot(t_all *g, t_data img);

#endif
