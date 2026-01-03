/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:39:52 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/21 16:43:21 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_quotes(char c, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		if (!*quote_char)
			*quote_char = c;
		else if (*quote_char == c)
			*quote_char = 0;
	}
}

void	handle_token_count(char c, const char *delim, int *inside_token,
		size_t *tokens)
{
	if (!ft_strchr(delim, c) && !*inside_token)
	{
		(*tokens)++;
		*inside_token = 1;
	}
	else if (ft_strchr(delim, c))
	{
		if (!ft_isspace(c))
			(*tokens)++;
		*inside_token = 0;
	}
}

int	handle_redirections(char const **s, int *inside_token, size_t *tokens)
{
	if ((**s == '<' && *(*s + 1) == '<') || (**s == '>' && *(*s + 1) == '>'))
	{
		if (*inside_token)
		{
			(*tokens)++;
			*inside_token = 0;
		}
		(*tokens)++;
		(*s) += 1;
		return (1);
	}
	else if (**s == '<' || **s == '>' || **s == '|')
	{
		if (*inside_token)
		{
			(*tokens)++;
			*inside_token = 0;
		}
		(*tokens)++;
		return (1);
	}
	return (0);
}
