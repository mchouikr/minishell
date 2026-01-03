/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:26:08 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/25 19:20:36 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	new_file_node(t_command *cmd)
{
	t_file_data	*new_node;

	new_node = malloc(sizeof(t_file_data));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->prev = cmd->file_data;
	new_node->limiter = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = NULL;
	cmd->file_data->next = new_node;
}

void	handle_limiter(t_command *cmd, char *token, int *j)
{
	if (cmd->limiter && cmd->limiter[*j] && ft_strcmp(token,
			cmd->limiter[*j]) == 0)
	{
		cmd->file_data->limiter = ft_strdup(cmd->limiter[*j]);
		if (!cmd->file_data->next)
			new_file_node(cmd);
		cmd->file_data = cmd->file_data->next;
		(*j)++;
	}
}

void	handle_append(t_command *cmd, char *token, int *m)
{
	if (cmd->append && cmd->append[*m] && ft_strcmp(token,
			cmd->append[*m]) == 0)
	{
		cmd->file_data->append = ft_strdup(cmd->append[*m]);
		if (!cmd->file_data->next)
			new_file_node(cmd);
		cmd->file_data = cmd->file_data->next;
		(*m)++;
	}
}

void	handle_infile_m(t_command *cmd, char *token, int *k)
{
	if (cmd->infile && cmd->infile[*k] && ft_strcmp(token,
			cmd->infile[*k]) == 0)
	{
		cmd->file_data->infile = ft_strdup(cmd->infile[*k]);
		if (!cmd->file_data->next)
			new_file_node(cmd);
		cmd->file_data = cmd->file_data->next;
		(*k)++;
	}
}

void	handle_outfile_m(t_command *cmd, char *token, int *l)
{
	if (cmd->outfile && cmd->outfile[*l] && ft_strcmp(token,
			cmd->outfile[*l]) == 0)
	{
		cmd->file_data->outfile = ft_strdup(cmd->outfile[*l]);
		if (!cmd->file_data->next)
			new_file_node(cmd);
		cmd->file_data = cmd->file_data->next;
		(*l)++;
	}
}

// void	file_management(t_command *cmd, t_input *input)
// {
// 	int			i;
// 	int			j;
// 	int			k;
// 	int			l;
// 	int			m;
// 	t_file_data	*new_node;
// 	t_file_data	*head;

// 	if (!cmd->file_data || !input->parsed)
// 		return ;
// 	i = 0;
// 	while (cmd)
// 	{
// 		head = cmd->file_data;
// 		i = 0;
// 		j = 0;
// 		k = 0;
// 		l = 0;
// 		m = 0;
// 		while (input->parsed[i])
// 		{
// 			if (cmd->limiter && cmd->limiter[j] && ft_strcmp(input->parsed[i],
// 					cmd->limiter[j]) == 0)
// 			{
// 				cmd->file_data->limiter = ft_strdup(cmd->limiter[j]);
// 				if (!cmd->file_data->next)
// 					new_file_node(new_node, cmd);
// 				cmd->file_data = cmd->file_data->next;
// 				j++;
// 			}
// 			else if (cmd->append && cmd->append[m]
// 				&& ft_strcmp(input->parsed[i], cmd->append[m]) == 0)
// 			{
// 				cmd->file_data->append = ft_strdup(cmd->append[m]);
// 				if (!cmd->file_data->next)
// 					new_file_node(new_node, cmd);
// 				cmd->file_data = cmd->file_data->next;
// 				m++;
// 			}
// 			else if (cmd->infile && cmd->infile[k]
// 				&& ft_strcmp(input->parsed[i], cmd->infile[k]) == 0)
// 			{
// 				cmd->file_data->infile = ft_strdup(cmd->infile[k]);
// 				if (!cmd->file_data->next)
// 					new_file_node(new_node, cmd);
// 				cmd->file_data = cmd->file_data->next;
// 				k++;
// 			}
// 			else if (cmd->outfile && cmd->outfile[l]
// 				&& ft_strcmp(input->parsed[i], cmd->outfile[l]) == 0)
// 			{
// 				cmd->file_data->outfile = ft_strdup(cmd->outfile[l]);
// 				if (!cmd->file_data->next && cmd->outfile[l])
// 					new_file_node(new_node, cmd);
// 				cmd->file_data = cmd->file_data->next;
// 				l++;
// 			}
// 			i++;
// 		}
// 		cmd->file_data = head;
// 		cmd = cmd->next;
// 	}
// }
