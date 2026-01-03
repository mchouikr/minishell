/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:48:22 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/21 16:33:18 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_heredoc_redir(char **tokens, int i, t_command *cmd)
{
	char	*tmp;

	if (tokens[i + 1] && (ft_strncmp(tokens[i + 1], "<<", 2) == 0
			|| ft_strncmp(tokens[i + 1], "<", 1) == 0 || ft_strncmp(tokens[i
					+ 1], ">>", 2) == 0))
	{
		if (tokens[i + 2] && ft_strncmp(tokens[i + 2], "<", 1) == 0)
			return (handle_syntax_error("<<"));
		return (handle_syntax_error("<"));
	}
	else if (tokens[i + 1] && ft_strncmp(tokens[i + 1], "|", 1) != 0)
	{
		tmp = ft_strdup(tokens[i + 1]);
		cmd->limiter[cmd->limiter_count] = remove_double_quotes((tokens[i
					+ 1]), cmd);
		cmd->limiter_count++;
		cmd->heredoc = 1;
		free(tmp);
	}
	else
		return (handle_syntax_error("newline"));
	if (tokens[i + 1] != NULL)
		i++;
	return (i);
}

static void	outfile_redir(char *tmp, t_command *cmd, char **tokens, int *i)
{
	tmp = ft_strdup(tokens[*i + 1]);
	cmd->outfile[cmd->outfile_count] = remove_double_quotes(tmp, cmd);
	cmd->outfile_count++;
	free(tmp);
}

static void	infile_redir(char *tmp, t_command *cmd, char **tokens, int *i)
{
	tmp = ft_strdup(tokens[*i + 1]);
	cmd->infile[cmd->infile_count] = remove_double_quotes(tmp, cmd);
	cmd->infile_count++;
	free(tmp);
}

int	handle_basic_redirect(char **tokens, int i, t_command *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(tokens[i], ">", 1) == 0)
	{
		if (tokens[i + 1] && ft_strncmp(tokens[i + 1], ">", 1) != 0
			&& ft_strncmp(tokens[i + 1], "<", 1) != 0 && ft_strncmp(tokens[i
					+ 1], "|", 1) != 0)
			outfile_redir(tmp, cmd, tokens, &i);
		else
			return (handle_syntax_error(">"));
	}
	else if (ft_strncmp(tokens[i], "<", 1) == 0)
	{
		if (tokens[i + 1] && ft_strncmp(tokens[i + 1], "<", 1) != 0
			&& ft_strncmp(tokens[i + 1], ">", 1) != 0 && ft_strncmp(tokens[i
					+ 1], "|", 1) != 0)
		{
			infile_redir(tmp, cmd, tokens, &i);
		}
		else
			return (handle_syntax_error("<"));
	}
	return (i + 1);
}

void	add_command_and_args(t_command *cmd, char *token, int *arg_index)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (!cmd || !arg_index || !token || *token == '\0')
		return ;
	tmp2 = ft_strdup(token);
	tmp = remove_double_quotes(tmp2, cmd);
	if (!cmd->cmd)
		cmd->cmd = tmp;
	if (!cmd->args)
		return ;
	cmd->args[(*arg_index)++] = tmp;
	if (cmd->args[*arg_index])
		free(cmd->args[*arg_index]);
	cmd->args[*arg_index] = NULL;
	free(tmp2);
}
