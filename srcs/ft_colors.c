/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:31:25 by nflan             #+#    #+#             */
/*   Updated: 2022/03/22 16:07:13 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_man_color(void)
{
	ft_printf("Voici les couleurs possibles a donner en 4eme argument si besoin :\n\n");
	ft_printf("Noir\t= 0\n");
	ft_printf("Rouge\t= 1\n");
	ft_printf("Vert\t= 2\n");
	ft_printf("Bleu\t= 3\n");
	ft_printf("Jaune\t= 12\n");
	ft_printf("Blanc\t= 255\n");
	exit (0);
}

int	ft_deg(int iteration, int max, int t, int i)
{
	int	color;

	color = iteration * 255 / max;
	if (i == 0)
		return (create_trgb(t, 0, 0, 0));
	else if (i == 1)
		return (create_trgb(t, color, 0, 0));
	else if (i == 2)
		return (create_trgb(t, 0, color, 0));
	else if (i == 3)
		return (create_trgb(t, 0, 0, color));
	else if (i == 12)
		return (create_trgb(t, color, color, 0));
	else if (i == 255)
		return (create_trgb(t, color, color, color));
	else
		return (0);
}
