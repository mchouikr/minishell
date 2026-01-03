/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:51:37 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/26 19:35:16 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_syntax_error(char *msg)
{
	ft_fprintf(2, "minishell : syntax error near unexpected token `%s'\n", msg);
	return (-1);
}

int	check_initial_syntax(char **tokens)
{
	if (tokens[0] && !tokens[1] && (ft_strncmp(tokens[0], "<", 1) == 0
			|| ft_strncmp(tokens[0], ">", 1) == 0))
		return (handle_syntax_error("newline"));
	if (tokens[0] && ft_strncmp(tokens[0], "|", 1) == 0)
		return (handle_syntax_error("|"));
	return (0);
}

int	handle_pipe(char **tokens, int i, t_command *cmd)
{
	if (tokens[i + 1] && ft_strncmp(tokens[i + 1], "|", 1) != 0)
	{
		cmd->next = parse_tokens(tokens + i + 1);
		if (!cmd->next)
			return (-1);
		if (cmd->next)
			cmd->next->prev = cmd;
	}
	else
		return (handle_syntax_error("|"), -1);
	return (i);
}

int	handle_append_redir(char **tokens, int i, t_command *cmd)
{
	char	*tmp;

	if (tokens[i + 1] && (ft_strncmp(tokens[i + 1], ">>", 2) == 0
			|| ft_strncmp(tokens[i + 1], ">", 1) == 0 || ft_strncmp(tokens[i
					+ 1], "<<", 1) == 0))
	{
		if (tokens[i + 2] && ft_strncmp(tokens[i + 2], ">", 1) == 0)
			return (handle_syntax_error(">>"));
		return (handle_syntax_error(">"));
	}
	else if (tokens[i + 1] && ft_strncmp(tokens[i + 1], "|", 1) != 0)
	{
		tmp = ft_strdup(tokens[i + 1]);
		cmd->append[cmd->append_count] = remove_double_quotes(tmp, cmd);
		cmd->append_count++;
		cmd->append_flag = 1;
		free(tmp);
	}
	else
		return (handle_syntax_error("newline"));
	if (tokens[i + 1] != NULL)
		i++;
	return (i);
}
