/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_helper2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:36:03 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/28 14:13:28 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_token_helper(char **tokens, int i, t_command *cmd,
		int *arg_index)
{
	while (tokens[i])
	{
		if (tokens[i] && ft_strncmp(tokens[i], "|", 1) == 0)
		{
			i = handle_pipe(tokens, i, cmd);
			break ;
		}
		if (tokens[i] && ft_strncmp(tokens[i], ">>", 2) == 0)
			i = handle_append_redir(tokens, i, cmd);
		else if (tokens[i] && ft_strncmp(tokens[i], "<<", 2) == 0)
			i = handle_heredoc_redir(tokens, i, cmd);
		else if (tokens[i] && (ft_strncmp(tokens[i], ">", 1) == 0
				|| ft_strncmp(tokens[i], "<", 1) == 0))
			i = handle_basic_redirect(tokens, i, cmd);
		else
			add_command_and_args(cmd, tokens[i], arg_index);
		if (i == -1)
			break ;
		else
			i++;
	}
	return (i);
}

void	nullify_cmd(t_command *cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->limiter = NULL;
	cmd->append = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->append_flag = 0;
	cmd->heredoc = 0;
}

t_token_counts	count_parsed_tokens(char **tokens)
{
	t_token_counts	counts;
	int				i;

	ft_memset(&counts, 0, sizeof(counts));
	i = 0;
	while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
			counts.heredoc_count++;
		if (ft_strcmp(tokens[i], ">>") == 0)
			counts.append_count++;
		else if (ft_strcmp(tokens[i], "<") == 0)
			counts.in_count++;
		else if (ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i],
				">>") == 0)
			counts.out_count++;
		else
			counts.arg_count++;
		i++;
	}
	return (counts);
}

void	cmd_fail_2(t_command *cmd)
{
	if (cmd)
		free_command(cmd);
}

t_command	*parse_tokens(char **tokens)
{
	t_command		*cmd;
	int				arg_index;
	int				i;
	t_token_counts	counts;

	if (!tokens)
		return (NULL);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (perror("Failed to alloc command list\n"), NULL);
	nullify_cmd(cmd);
	counts = count_parsed_tokens(tokens);
	if (counts.arg_count + counts.in_count + counts.out_count
		+ counts.heredoc_count >= ((INPUT_MAX / 8) - 8))
		return (NULL);
	if (command_init(cmd, counts) == -1)
		return (NULL);
	if (check_initial_syntax(tokens))
		return (free_command(cmd), NULL);
	arg_index = 0;
	i = parse_token_helper(tokens, 0, cmd, &arg_index);
	if (i == -1)
		return (free_command(cmd), NULL);
	return (cmd);
}
