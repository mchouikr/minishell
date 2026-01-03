/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:16:40 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/28 14:17:10 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_file_data_node(t_file_data *node)
{
	if (!node)
		return ;
	if (node->limiter)
	{
		free(node->limiter);
		node->limiter = NULL;
	}
	if (node->infile)
	{
		free(node->infile);
		node->infile = NULL;
	}
	if (node->outfile)
	{
		free(node->outfile);
		node->outfile = NULL;
	}
	if (node->append)
	{
		free(node->append);
		node->append = NULL;
	}
	if (node)
		free(node);
}

void	free_file_data(t_file_data *file_data)
{
	t_file_data	*current;
	t_file_data	*next;

	if (!file_data)
		return ;
	current = file_data;
	while (current && current->prev)
		current = current->prev;
	while (current)
	{
		next = current->next;
		free_file_data_node(current);
		current = next;
	}
}

int	init_command_array(t_command *cmd, t_token_counts counts)
{
	cmd->args = ft_calloc(counts.arg_count + 1, sizeof(char *));
	if (!cmd->args)
		return (perror("Failed to init args"), -1);
	cmd->infile = ft_calloc(counts.in_count + 1, sizeof(char *));
	if (!cmd->infile)
		return (perror("Failed to init infile\n"), -1);
	cmd->outfile = ft_calloc(counts.out_count + 1, sizeof(char *));
	if (!cmd->outfile)
		return (perror("Failed to init infile\n"), -1);
	cmd->limiter = ft_calloc(counts.heredoc_count + 1, sizeof(char *));
	if (!cmd->limiter)
		return (perror("Failed to init limiter\n"), -1);
	cmd->append = ft_calloc(counts.append_count + 1, sizeof(char *));
	if (!cmd->append)
		return (perror("Failed to init append\n"), -1);
	return (0);
}
