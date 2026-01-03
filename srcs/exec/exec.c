/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:18:31 by mchouikr          #+#    #+#             */
/*   Updated: 2026/01/03 11:14:22 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_and_fill_heredocs(t_command *cmd, t_data *data)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		if (current->heredoc == 1)
		{
			data->heredoc_flag = 1;
			if (ft_heredoc(current, data) != 0)
				return (1);
			if (current->cmd == NULL)
				data->hd_with_no_cmd = 1;
		}
		current = current->next;
	}
	return (0);
}

int	execution(t_command *cmd, t_data *data, t_input *input)
{
	pid_t	pid;

	pid = 0;
	data->cmd_nbr = ft_cmd_index(cmd);
	if (data->cmd_nbr != 0)
	{
		if (data->cmd_nbr == 1 && is_builtin(cmd) == 1)
		{
			if (check_and_fill_heredocs(cmd, data) == 1)
				return (1);
			single_builtin(cmd, data, input);
		}
		else
		{
			dup_for_exec(cmd, data);
			if (check_and_fill_heredocs(cmd, data) == 1)
				return (1);
			exec_loop(cmd, data, input, pid);
		}
	}
	return (0);
}

void	exec_loop(t_command *cmd, t_data *data, t_input *input, pid_t pid)
{
	while (cmd)
	{
		if (data->cmd_nbr > 1)
		{
			if (pipe(data->fd) == -1)
				return ;
		}
		if (cmd->cmd == NULL)
			break ;
		else
		{
			signal(SIGQUIT, SIG_DFL);
			pid = fork();
		}
		data->childs++;
		if (pid < 0)
			return ;
		if (pid == 0)
			child_process(cmd, data, input);
		else
			handle_parent(data, cmd, pid);
		ignore_signal();
		cmd = cmd->next;
	}
	close_and_wait(data, pid);
}

int	handle_files(t_command *cmd, t_data *data)
{
	t_file_data	*current;

	current = cmd->file_data;
	while (current != NULL)
	{
		if (opening_files(cmd, data, current) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}
