/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:40:57 by edelplan          #+#    #+#             */
/*   Updated: 2024/06/03 16:52:21 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t size)
{
	unsigned char	*ptr;

	if (!size && nelem * size > SIZE_MAX)
		return (NULL);
	ptr = (void *)malloc(nelem * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nelem * size);
	return (ptr);
}
