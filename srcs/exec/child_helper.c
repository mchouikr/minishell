/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:03:41 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/28 14:02:58 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_command *cmd, t_data *data, t_input *input)
{
	int	exit_code;
	int	file_status;

	exit_code = 0;
	file_status = 0;
	file_status = handle_files(cmd, data);
	if (file_status == 1)
		handle_file_error(cmd, data, input);
	if (data->new_stdin > 2)
	{
		dup2(data->new_stdin, STDIN_FILENO);
		close(data->new_stdin);
	}
	dup_and_close_in_child(cmd, data);
	if (is_builtin(cmd) == 1)
		execute_builtin_in_pipe(cmd, data, input);
	else
		execute_in_child(cmd, data, input, exit_code);
}

void	dup_and_close_in_child(t_command *cmd, t_data *data)
{
	if (cmd->next != NULL)
	{
		if (cmd->outfile[0] == NULL || cmd->append[0] == NULL)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			dup2(data->fd[1], STDERR_FILENO);
		}
	}
	if (data->new_stdout > 2)
	{
		dup2(data->new_stdout, STDOUT_FILENO);
		close(data->new_stdout);
	}
	if (data->fd[0] > 2)
		close(data->fd[0]);
	if (data->fd[1] > 2)
		close(data->fd[1]);
	if (data->stdin_backup > 2)
		close(data->stdin_backup);
	if (data->stdout_backup > 2)
		close(data->stdout_backup);
	if (cmd->infile[0])
		close(data->stdin_backup);
}

int	exit_and_free(t_command *cmd, t_data *data, t_input *input)
{
	int	exit_code;

	exit_code = data->exit_status;
	free_command(cmd);
	ft_free(input->parsed);
	free(input);
	exit_code = data->exit_status;
	free_data(data);
	exit(exit_code);
}
