/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:51:37 by nflan             #+#    #+#             */
/*   Updated: 2022/03/18 18:19:07 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(int ac, char **av)
{
	char	*setup;
	char	*window;

	setup = NULL;
	window = NULL;
	if (ac != 2)
		return (1);
	setup = mlx_init();
	if (!setup)
	{
		perror("mlx init error");
		return (1);
	}
	window = mlx_new_window (setup, 600, 600, av[1]);
	if (!window)
	{
		perror("window error");
		return (1);
	}
	ft_printf("hello\n");
	mlx_loop(setup);
	return (0);
}
