/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:03:25 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/21 16:47:21 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cleanup_heredoc_files(t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->limiter_count)
	{
		if (cmd->heredoc_fds[i] != -1)
			unlink(cmd->hd_file_name[i]);
		i++;
	}
	if (cmd->hd_file_name)
		ft_free(cmd->hd_file_name);
}

void	free_command_single_node(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	if (tmp->args)
		ft_free(tmp->args);
	if (tmp->infile)
		ft_free(tmp->infile);
	if (tmp->outfile)
		ft_free(tmp->outfile);
	if (tmp->limiter)
		ft_free(tmp->limiter);
	if (tmp->heredoc_fds)
		free(tmp->heredoc_fds);
	free(tmp);
}

int	cmd_fail(t_input *input, t_data *data, t_command *cmd)
{
	int	exit_code;

	data->exit_status = 2;
	exit_code = data->exit_status;
	if (input->parsed)
		ft_free(input->parsed);
	free(input);
	free_command(cmd);
	return (exit_code);
}

// void	cleanup_cmd(t_command *cmd)
// {
// 	ft_free(cmd->args);
// 	ft_free(cmd->infile);
// 	ft_free(cmd->outfile);
// 	ft_free(cmd->limiter);
// 	free(cmd);
// }
