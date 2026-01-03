/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:37:26 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/25 16:40:16 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_and_wait(t_data *data, pid_t pid)
{
	if (data->new_stdin > 2)
		close(data->new_stdin);
	if (data->new_stdout > 2)
		close(data->new_stdout);
	if (data->fd[0] > 2)
		close(data->fd[0]);
	if (data->fd[1] > 2)
		close(data->fd[1]);
	wait_for_children(data, pid);
	if (data->stdin_backup > 2)
		close(data->stdin_backup);
	if (data->stdout_backup > 2)
		close(data->stdout_backup);
}

void	wait_for_children(t_data *data, pid_t pid)
{
	pid = waitpid(-1, &data->status, 0);
	while (pid > 0)
	{
		if (pid == -1)
		{
			if (errno != ECHILD)
				perror("waitpid");
			break ;
		}
		else if (pid == data->last_pid)
		{
			handle_last_process(data);
		}
		signal(SIGQUIT, SIG_IGN);
		pid = waitpid(-1, &data->status, 0);
	}
}

void	handle_last_process(t_data *data)
{
	exec_signal_sigint();
	if (WIFEXITED(data->status))
		data->exit_status = WEXITSTATUS(data->status);
	else if (WIFSIGNALED(data->status))
		data->exit_status = 128 + WTERMSIG(data->status);
	if (WIFSIGNALED(data->status))
	{
		if (WTERMSIG(data->status) == SIGQUIT)
		{
			if (data->exit_status == 131)
				ft_fprintf(2, "Quit (core dumped)\n");
		}
		if (WTERMSIG(data->status) == SIGINT)
			ft_fprintf(2, "\n");
	}
}
