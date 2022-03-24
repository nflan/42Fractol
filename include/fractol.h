/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:52:06 by nflan             #+#    #+#             */
/*   Updated: 2022/03/24 17:53:43 by nflan            ###   ########.fr       */
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

typedef struct s_all
{
	char		**av;
	void		*setup;
	void		*window;
	double		zoom;
	t_complex	c;
	int			pal[12];
	int			julia;
	int			width;
	int			height;
	int			ac;
	int			color;
	int			x;
	int			y;
	int			max;
	int			fractal;
	t_data		img;
	t_data		curr;
}	t_all;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_area
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	image_x;
	double	image_y;
	double	zoom_x;
	double	zoom_y;
	int		w;
	int		h;
}	t_area;

// MAIN
int	create_trgb(int t, int r, int g, int b);
int	get_color(int trgb, int c);
int	ft_mandelbrot(t_all *g, t_data img);
int	ft_julia(t_all *g, t_data img);

// COLORS
int 	ft_deg(int iteration, t_all *g, int t, int i);
void	ft_init_color(t_all *g);
int		ft_print_new(t_all *g);
int		ft_change_color(int key, t_all *g);
int		ft_man_color(void);

#endif
