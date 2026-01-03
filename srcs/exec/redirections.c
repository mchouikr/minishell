/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:52:28 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 20:23:40 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	opening_files(t_command *cmd, t_data *data, t_file_data *current)
{
	if (current->infile != NULL)
	{
		if (infile_redirect(data, current) == 1)
			return (1);
	}
	else if (current->limiter != NULL)
	{
		if (heredoc_redirect(cmd, data) == 1)
			return (1);
	}
	else if (current->outfile != NULL)
	{
		if (outfile_redirect(data, current) == 1)
			return (1);
	}
	else if (current->append != NULL)
	{
		if (append_redirect(data, current) == 1)
			return (1);
	}
	return (0);
}

int	infile_redirect(t_data *data, t_file_data *current)
{
	if (data->new_stdin > 2)
		(close(data->new_stdin), data->new_stdin = -1);
	data->new_stdin = open(current->infile, O_RDONLY);
	if (data->new_stdin == -1)
	{
		error(current->infile, NO_SUCH_FILE);
		if (data->cmd_nbr == 1)
			data->exit_status = 1;
		return (1);
	}
	return (0);
}

int	heredoc_redirect(t_command *cmd, t_data *data)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (data->new_stdin > 2)
		(close(data->new_stdin), data->new_stdin = -1);
	data->new_stdin = open(cmd->hd_file_name[cmd->limiter_count - 1], O_RDONLY);
	if (data->new_stdin == -1)
	{
		error(cmd->hd_file_name[cmd->limiter_count - 1], NO_SUCH_FILE);
		if (data->cmd_nbr == 1)
			data->exit_status = 1;
		return (1);
	}
	if (cmd->heredoc == 1)
	{
		tmp_fd = open(cmd->hd_file_name[cmd->limiter_count - 1], O_RDONLY,
				0600);
		dup2(tmp_fd, STDIN_FILENO);
		if (tmp_fd != STDIN_FILENO)
			close(tmp_fd);
	}
	return (0);
}

int	outfile_redirect(t_data *data, t_file_data *current)
{
	if (data->new_stdout > 2)
		(close(data->new_stdout), data->new_stdout = -1);
	data->new_stdout = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (data->new_stdout == -1)
	{
		error(current->outfile, PERM_DENIED);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

int	append_redirect(t_data *data, t_file_data *current)
{
	if (data->new_stdout > 2)
		(close(data->new_stdout), data->new_stdout = -1);
	data->new_stdout = open(current->append, O_WRONLY | O_CREAT | O_APPEND,
			0666);
	if (data->new_stdout == -1)
	{
		error(current->append, PERM_DENIED);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}
