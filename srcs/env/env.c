/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:30:45 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 20:42:56 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabdup(char **src)
{
	int		i;
	char	**dest;
	char	*tmp;

	if (!src)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_tablen(src) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < ft_tablen(src))
	{
		tmp = ft_strdup(src[i]);
		if (!tmp)
		{
			while (--i >= 0)
				free(dest[i]);
			free(dest);
			return (NULL);
		}
		dest[i] = tmp;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
