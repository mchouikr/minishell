/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:48:32 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 20:59:10 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	infile_redirect_sg(t_data *data, t_file_data *current)
{
	data->new_stdin = open(current->infile, O_RDONLY);
	if (data->new_stdin == -1)
	{
		error(current->infile, NO_SUCH_FILE);
		if (data->cmd_nbr == 1)
			data->exit_status = 1;
		return (1);
	}
	if (data->new_stdin > 2)
	{
		dup2(data->new_stdin, STDIN_FILENO);
		close(data->new_stdin);
	}
	return (0);
}

int	heredoc_redirect_sg(t_command *cmd, t_data *data)
{
	data->new_stdin = open(cmd->hd_file_name[cmd->limiter_count - 1], O_RDONLY);
	if (data->new_stdin == -1)
	{
		error(cmd->hd_file_name[cmd->limiter_count - 1], NO_SUCH_FILE);
		if (data->cmd_nbr == 1)
			data->exit_status = 1;
		return (1);
	}
	if (data->new_stdin > 2)
	{
		dup2(data->new_stdin, STDIN_FILENO);
		close(data->new_stdin);
	}
	return (0);
}

int	outfile_redirect_sg(t_data *data, t_file_data *current, int i)
{
	if (i > 0 && data->new_stdout > 2)
		(close(data->new_stdout), data->new_stdout = -1);
	data->new_stdout = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (data->new_stdout == -1)
	{
		error(current->outfile, PERM_DENIED);
		data->exit_status = 1;
		return (1);
	}
	if (data->new_stdout > 2)
	{
		dup2(data->new_stdout, STDOUT_FILENO);
		close(data->new_stdout);
	}
	return (0);
}

int	append_redirect_sg(t_data *data, t_file_data *current, int i)
{
	if (i > 0 && data->new_stdout > 2)
		(close(data->new_stdout), data->new_stdout = -1);
	data->new_stdout = open(current->append, O_WRONLY | O_CREAT | O_APPEND,
			0666);
	if (data->new_stdout == -1)
	{
		error(current->append, PERM_DENIED);
		data->exit_status = 1;
		return (1);
	}
	if (data->new_stdout > 2)
	{
		dup2(data->new_stdout, STDOUT_FILENO);
		close(data->new_stdout);
	}
	return (0);
}
