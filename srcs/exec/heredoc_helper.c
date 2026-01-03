/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:45:15 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 21:13:19 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_heredocs_loop(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->limiter_count)
	{
		if (cmd->heredoc_fds[i] != -1)
			close(cmd->heredoc_fds[i]);
		i++;
	}
}

void	print_hd_error(int flag)
{
	if (flag == HEREDOC_WARNING)
		ft_fprintf(2,
			"minishell: warning heredocument delimited by end-of-file\n");
}

void	end_of_heredoc(char *line, char *limiter)
{
	if (!line || !ft_strcmp(line, limiter))
	{
		if (!line)
			print_hd_error(HEREDOC_WARNING);
		else
			free(line);
	}
}
