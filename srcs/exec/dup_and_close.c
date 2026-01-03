/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:30:28 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 17:15:35 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// laisser dup2 new_stdin sinon le pipe casse
// void	redirect_infile(t_command *cmd, t_data *data)
// {
// 	int	tmp_fd;

// 	tmp_fd = -1;
// 	// if (cmd->hd_file_name[cmd->limiter_count - 1] == data->new_stdin)
// 	if (cmd->heredoc == 1)
// 	{
// 		tmp_fd = open(cmd->hd_file_name[cmd->limiter_count - 1], O_RDONLY,
// 				0600);
// 		dup2(tmp_fd, STDIN_FILENO);
// 		if (tmp_fd != STDIN_FILENO)
// 			close(tmp_fd);
// 	}
// 	else if (data->new_stdin > 2)
// 	{
// 		dup2(data->new_stdin, STDIN_FILENO);
// 		close(data->new_stdin);
// 	}
// }

// Restaurer STDOUT quand heredoc sans commannde (pas de fork)
void	handle_heredoc_no_cmd(t_command *cmd, t_data *data)
{
	if (cmd->heredoc_fds[cmd->limiter_count - 1] > 2)
		close(cmd->heredoc_fds[cmd->limiter_count - 1]);
	if (data->fd[1] > 2)
		close(data->fd[1]);
	if (data->stdout_backup > 2)
	{
		dup2(data->stdout_backup, STDOUT_FILENO);
		close(data->stdout_backup);
	}
}

// Close the write end of the pipe in the parent
// Close the previous new_stdin if it's not standard input
//(if we are in a pipe and if there is another cmd)
// Assign the read end of the current pipe to new_stdin for the next command
// Close the read end of the pipe if there is no next command
// Restaurer STDOUT pour le parent si pas  de cmd->next
void	handle_parent(t_data *data, t_command *cmd, pid_t pid)
{
	if (cmd->heredoc == 1)
		reset_signal();
	if (data->cmd_nbr > 1)
	{
		if (data->fd[1] > 2)
			(close(data->fd[1]), data->fd[1] = -1);
		if (cmd->next != NULL)
		{
			if (data->new_stdin > 2)
				(close(data->new_stdin), data->new_stdin = -1);
			data->new_stdin = data->fd[0];
			data->fd[0] = -1;
		}
		else
		{
			if (data->fd[0] > 2)
				(close(data->fd[0]), data->fd[0] = -1);
		}
	}
	if (cmd->next == NULL)
	{
		data->last_pid = pid;
		dup2(data->stdout_backup, STDOUT_FILENO);
		close(data->stdout_backup);
	}
}
