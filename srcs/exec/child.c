/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:25:00 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/28 14:30:15 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_cmd(t_command *cmd, t_input *input, t_data *data)
{
	struct stat	st;

	if (stat(cmd->cmd, &st) == -1)
	{
		error(cmd->cmd, NO_SUCH_FILE);
		data->exit_status = 127;
		exit_and_free(cmd, data, input);
	}
	if (S_ISDIR(st.st_mode))
	{
		error(cmd->cmd, IS_A_DIRECTORY);
		data->exit_status = 126;
		exit_and_free(cmd, data, input);
	}
	if (access(cmd->cmd, X_OK) == -1)
	{
		error(cmd->cmd, PERM_DENIED);
		data->exit_status = 126;
		exit_and_free(cmd, data, input);
	}
}

void	execute_in_child(t_command *cmd, t_data *data, t_input *input,
		int exit_code)
{
	if (!cmd->cmd || !cmd->cmd[0])
	{
		error(cmd->cmd, CMD_NOT_FOUND);
		data->exit_status = 127;
		exit_and_free(cmd, data, input);
	}
	if (ft_strchr(cmd->cmd, '/'))
		check_cmd(cmd, input, data);
	if (!init_path(cmd, data) && is_valid(cmd, data, data->path))
	{
		exit_and_free(cmd, data, input);
	}
	else
	{
		if (is_existing(cmd->cmd, data->mini_env) == 1 && cmd->cmd[0] == '/')
		{
			error(cmd->cmd, NO_SUCH_FILE);
			data->exit_status = 127;
			exit_and_free(cmd, data, input);
		}
		reset_signal();
		ft_execve(cmd, data, input, exit_code);
	}
}

void	ft_execve(t_command *cmd, t_data *data, t_input *input, int exit_code)
{
	if (execve(data->path, cmd->args, data->mini_env) == -1)
	{
		ignore_signal();
		free_command(cmd);
		ft_free(input->parsed);
		free(input);
		perror("execve");
		data->exit_status = 126;
		exit_code = data->exit_status;
		free_data(data);
		exit(exit_code);
	}
}

void	execute_builtin_in_pipe(t_command *cmd, t_data *data, t_input *input)
{
	int		exit_code;
	t_data	*temp;

	exec_builtin(cmd, data, input);
	exit_code = data->exit_status;
	if (data->mini_env)
	{
		temp = data;
		free_data(data);
		data = temp;
	}
	free_command(cmd);
	ft_free(input->parsed);
	free(input);
	exit(exit_code);
}
