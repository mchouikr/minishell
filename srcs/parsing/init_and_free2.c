/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:46:44 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/28 14:11:34 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	init_heredoc(t_command *cmd, t_token_counts counts)
{
	int	i;

	cmd->limiter_count = 0;
	cmd->heredoc = 0;
	if (counts.heredoc_count > 0)
	{
		cmd->heredoc_fds = ft_calloc(counts.heredoc_count, sizeof(int));
		if (!cmd->heredoc_fds)
			return (perror("Failed to init infile\n"), -1);
		i = 0;
		while (i < counts.heredoc_count)
			cmd->heredoc_fds[i++] = -1;
		cmd->hd_file_name = ft_calloc(counts.heredoc_count + 1, sizeof(char *));
		if (!cmd->hd_file_name)
			return (perror("Failed to init hd_file_name\n"), -1);
	}
	else
	{
		cmd->heredoc_fds = 0;
		cmd->hd_file_name = NULL;
	}
	return (0);
}

int	file_data_init(t_command *cmd)
{
	cmd->file_data = malloc(sizeof(t_file_data));
	if (!cmd->file_data)
		return (perror("Failed to init infile data\n"), -1);
	cmd->file_data->limiter = NULL;
	cmd->file_data->infile = NULL;
	cmd->file_data->outfile = NULL;
	cmd->file_data->next = NULL;
	cmd->file_data->append = NULL;
	cmd->file_data->prev = NULL;
	cmd->file_data->next = NULL;
	return (0);
}

int	command_init(t_command *cmd, t_token_counts counts)
{
	cmd->cmd = NULL;
	if (init_command_array(cmd, counts) != 0)
		return (-1);
	if (file_data_init(cmd) != 0)
		return (-1);
	cmd->infile_count = 0;
	cmd->outfile_count = 0;
	cmd->append_count = 0;
	cmd->append_flag = 0;
	cmd->quote_status = 0;
	if (init_heredoc(cmd, counts) != 0)
		return (-1);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (0);
}

static void	free_command_helper(t_command *tmp)
{
	if (!tmp)
		return ;
	if (tmp->args)
		ft_free(tmp->args);
	if (tmp->infile)
		ft_free(tmp->infile);
	if (tmp->outfile)
		ft_free(tmp->outfile);
	if (tmp->limiter)
		ft_free(tmp->limiter);
	if (tmp->append)
		ft_free(tmp->append);
	if (tmp->hd_file_name)
		cleanup_heredoc_files(tmp);
	if (tmp->heredoc_fds)
		free(tmp->heredoc_fds);
	if (tmp->file_data)
		free_file_data(tmp->file_data);
}

void	free_command(t_command *cmd)
{
	t_command	*head;
	t_command	*tmp;

	if (!cmd)
		return ;
	head = cmd;
	while (head->prev != NULL)
		head = head->prev;
	while (head)
	{
		tmp = head;
		head = head->next;
		free_command_helper(tmp);
		free(tmp);
	}
}
