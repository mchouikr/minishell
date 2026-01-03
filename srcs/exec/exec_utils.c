/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:42:10 by mchouikr          #+#    #+#             */
/*   Updated: 2026/01/03 11:14:32 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_paths(char **paths, char *cmd)
{
	char	*path;
	char	*part_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free(paths), path);
		free(path);
	}
	return (ft_free(paths), NULL);
}

char	*find_path(char *cmd, char **env, int i)
{
	char	**paths;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (check_paths(paths, cmd));
}

int	ft_cmd_index(t_command *cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (0);
	while (cmd != NULL)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

