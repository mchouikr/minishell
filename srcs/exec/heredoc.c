/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:04:34 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 20:46:29 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("/tmp/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	ft_heredoc_loop(char *limiter, t_data *data, int write_fd)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	while (1)
	{
		line = readline(">");
		if (g_signal == 2)
		{
			if (line)
				free(line);
			if (write_fd != -1)
				close(write_fd);
			return (130);
		}
		if (!line || !ft_strcmp(line, limiter))
			return (end_of_heredoc(line, limiter), 1);
		tmp = find_dollar_heredoc(line, data);
		(free(line), ft_putendl_fd(tmp, write_fd), free(tmp));
	}
	close(write_fd);
	return (0);
}

int	ft_heredoc(t_command *cmd, t_data *data)
{
	int	i;
	int	stdin_backup;

	i = -1;
	stdin_backup = dup(STDIN_FILENO);
	while (++i < cmd->limiter_count)
	{
		cmd->hd_file_name[i] = generate_heredoc_filename();
		cmd->heredoc_fds[i] = open(cmd->hd_file_name[i],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->heredoc_fds[i] == -1)
			return (perror("open heredoc file"), exit(1), 1);
		heredoc_signals();
		if (ft_heredoc_loop(cmd->limiter[i], data, cmd->heredoc_fds[i]) == 130)
			return (handle_heredoc_global(cmd, data, stdin_backup),
				data->exit_status);
		if (cmd->heredoc_fds[i] > 2)
			close(cmd->heredoc_fds[i]);
	}
	if (stdin_backup > 2)
		close(stdin_backup);
	if (data->new_stdin > 2)
		close(data->new_stdin);
	reset_signal();
	return (0);
}

void	handle_heredoc_global(t_command *cmd, t_data *data, int stdin_backup)
{
	close_heredocs_loop(cmd);
	dup2(stdin_backup, STDIN_FILENO);
	if (stdin_backup != -1)
		close(stdin_backup);
	data->exit_status = 130;
	reset_signal();
}
