/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:58:33 by nflan             #+#    #+#             */
/*   Updated: 2022/02/16 12:20:07 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tab;

	tab = malloc(nmemb * size);
	if (!tab)
		return (0);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
