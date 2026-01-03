/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:47:36 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 20:55:51 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// check if cmd exists (not if it is executable)
// returns 0 in case of error
// returns 1 if path is valid
// returns 2 if path is directly specified and file exists

static int	check_paths(char **possible_paths, char *cmd)
{
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (possible_paths[i])
	{
		part_path = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (!part_path || !path)
		{
			free(part_path);
			free(path);
			return (0);
		}
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	is_existing(char *cmd, char **env)
{
	char	**possible_paths;
	int		result;

	if (cmd == NULL || !cmd || !env)
		return (0);
	if (access(cmd, F_OK) == 0)
		return (2);
	possible_paths = get_possible_paths(env);
	if (!possible_paths)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			cmd);
		return (0);
	}
	result = check_paths(possible_paths, cmd);
	ft_free(possible_paths);
	return (result);
}

int	stat_failed(struct stat filestat, t_command *cmd, t_data *data, char *path)
{
	if (S_ISREG(filestat.st_mode) && access(path, X_OK) < 0)
	{
		error(cmd->cmd, CMD_NOT_FOUND);
		data->exit_status = 127;
		return (1);
	}
	if (is_existing(path, data->mini_env))
		return (0);
	else
	{
		if (errno == ENOENT)
			return (error(cmd->cmd, NO_SUCH_FILE), data->exit_status = 127, 1);
		else if (errno == EACCES)
			return (error(cmd->cmd, PERM_DENIED), data->exit_status = 126, 1);
		else if (errno == EFAULT)
		{
			error(cmd->cmd, CMD_NOT_FOUND);
			data->exit_status = 127;
			return (1);
		}
	}
	return (1);
}

int	is_valid(t_command *cmd, t_data *data, char *path)
{
	struct stat	filestat;
	int			status;

	status = stat(path, &filestat);
	ft_memset(&filestat, 0, sizeof(filestat));
	if (status < 0)
		return (stat_failed(filestat, cmd, data, path));
	else
	{
		if (S_ISDIR(filestat.st_mode))
		{
			return (error(cmd->cmd, IS_A_DIRECTORY), data->exit_status = 126,
				1);
		}
		else if (!S_ISDIR(filestat.st_mode))
		{
			error(cmd->cmd, CMD_NOT_FOUND);
			data->exit_status = 127;
			return (127);
		}
	}
	return (0);
}

int	init_path(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	data->path = find_path(cmd->cmd, data->mini_env, i);
	if (!data->path)
	{
		if (is_existing(cmd->cmd, data->mini_env) != 0)
		{
			data->exit_status = 127;
		}
		return (0);
	}
	return (1);
}

// int	is_existing(char *cmd, char **env)
// {
// 	char	**possible_paths;
// 	char	*path;
// 	int		i;
// 	char	*part_path;

// 	i = -1;
// 	possible_paths = NULL;
// 	path = NULL;
// 	if (cmd == NULL || !cmd || !env)
// 		return (0);
// 	if (access(cmd, F_OK) == 0)
// 		return (2);
// 	possible_paths = get_possible_paths(env);
// 	if (!possible_paths)
// 		return (ft_fprintf(STDERR_FILENO, "minishell: %s:
// No such file or directory\n", cmd), 0);
// 	while (possible_paths[++i])
// 	{
// 		part_path = ft_strjoin(possible_paths[i], "/");
// 		path = ft_strjoin(part_path, cmd);
// 		if (!part_path || !path)
// 			return (ft_free(possible_paths), free(part_path), free(path), 0);
// 		free(part_path);
// 		if (access(path, F_OK) == 0)
// 			return (ft_free(possible_paths), free(path), 1);
// 		free(path);
// 	}
// 	return (ft_free(possible_paths), 0);
// }
