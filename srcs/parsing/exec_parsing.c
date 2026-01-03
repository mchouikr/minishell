/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:48:05 by edelplan          #+#    #+#             */
/*   Updated: 2024/10/17 17:15:21 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//STOPPED HERE

int	is_exec(char *cmd, char **env)
{
	char	**possible_paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	possible_paths = NULL;
	path = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (2);
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	possible_paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (possible_paths[++i])
	{
		part_path = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free(possible_paths), free(path), 1);
		free(path);
	}
	return (ft_free(possible_paths), 0);
}
