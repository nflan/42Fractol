/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:07 by nflan             #+#    #+#             */
/*   Updated: 2022/04/05 15:46:49 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol_bonus.h"

char	**ft_parse_nbr(char **av)
{
	if (av[2] && !ft_strncmp(av[2], "max", 4))
		av[2] = "2560";
	else if (av[2] && !ft_strncmp(av[2], "min", 4))
		av[2] = "150";
	if (av[3] && !ft_strncmp(av[3], "max", 4))
		av[3] = "1355";
	else if (av[3] && !ft_strncmp(av[3], "min", 4))
		av[3] = "150";
	return (av);
}

int	ft_compare(char **av)
{
	int	i;

	i = 0;
	if (av[1])
	{
		av[1] = ft_strlower(av[1]);
		if (ft_strncmp(av[1], "julia", 6))
			i++;
		if (ft_strncmp(av[1], "mandelbrot", 11))
			i++;
		if (ft_strncmp(av[1], "glynn", 6))
			i++;
		if (i == 2)
			return (0);
	}
	ft_putstr_fd("L'argument 1 est Julia ou Mandelbrot ou Glynn\n", 2);
	return (1);
}

int	ft_error_parse(void)
{
	ft_putstr_fd("La fonction s'execute comme suit :\
			\nav[1] = nom de la fractale\nav[2] = width (150 <= int <= 2560)\
			\nav[3] = height (150 <= int <= 1355)\
			\nav[2] et av[3] : Pour le min et max, tu peux ecrire min ou max\
			\nav[4] = color (0 <= int <= 255) (tu peux executer la\
 commande \"./fractor color\" pour plus d'informations).\
			\nav[5] = ensemble de Julia (0 par defaut)\n", 2);
	exit (1);
}

int	ft_parse(int ac, char **av, int i)
{
	if (av[1] && !ft_strncmp(av[1], "color", 6))
		ft_man_color();
	i += ft_compare(av);
	if (av[2] || av[3])
		av = ft_parse_nbr(av);
	if (!av[2] || ft_atoi(av[2]) < 150 || ft_atoi(av[2]) > 2560)
		i += ft_putstr_fd("Le 2eme arg doit etre un int >= 150 et <= 2560\n", 2);
	if (!av[3] || ft_atoi(av[3]) < 150 || ft_atoi(av[3]) > 1355)
		i += ft_putstr_fd("Le 3eme arg doit etre un int >= 150 et <= 1355\n", 2);
	if (ac > 5 && (ft_atoi(av[5]) < 0 || ft_atoi(av[5]) > 9))
		i += ft_putstr_fd("Les ensembles de Julia traites vont de 0 a 9\n", 2);
	if (ac < 4 || ac > 6 || i)
		ft_error_parse();
	return (0);
}
