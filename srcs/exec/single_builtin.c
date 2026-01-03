/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:29:16 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 21:13:34 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	single_builtin(t_command *cmd, t_data *data, t_input *input)
{
	int	file_status;

	file_status = 0;
	data->single_builtin_flag = 1;
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	file_status = file_single_builtin(cmd, data);
	if (file_status != 0)
	{
		restore_stds(data);
		return ;
	}
	exec_builtin(cmd, data, input);
	restore_stds(data);
}

void	restore_stds(t_data *data)
{
	if (data->saved_stdin > 2)
	{
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
	}
	if (data->saved_stdout > 2)
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		close(data->saved_stdout);
	}
}

int	file_single_builtin(t_command *cmd, t_data *data)
{
	t_file_data	*current;
	int			i;

	i = 0;
	current = cmd->file_data;
	while (current != NULL)
	{
		if (file_mgmt_sg(cmd, data, current, i) == 1)
			return (1);
		i++;
		current = current->next;
	}
	return (0);
}

int	file_mgmt_sg(t_command *cmd, t_data *data, t_file_data *current, int i)
{
	if (current->infile != NULL)
	{
		if (infile_redirect_sg(data, current) == 1)
			return (1);
	}
	else if (current->limiter != NULL)
	{
		if (heredoc_redirect_sg(cmd, data) == 1)
			return (1);
	}
	else if (current->outfile != NULL)
	{
		if (outfile_redirect_sg(data, current, i) == 1)
			return (1);
	}
	else if (current->append != NULL)
	{
		if (append_redirect_sg(data, current, i) == 1)
			return (1);
	}
	return (0);
}
