/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:52:06 by nflan             #+#    #+#             */
/*   Updated: 2022/03/22 16:01:39 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"

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
	char	**av;
	void	*setup;
	void	*window;
	int		width;
	int		height;
	int		ac;
	int		color;
	t_data	img;
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

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

// MAIN
int	create_trgb(int t, int r, int g, int b);

// COLORS
int ft_deg(int iteration, int max, int t, int i);
int	ft_man_color(void);

#endif
