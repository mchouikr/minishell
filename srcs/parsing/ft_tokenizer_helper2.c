/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_helper2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:40:48 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/21 16:43:46 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	safe_malloc(char **array, int position, size_t buffer)
{
	int	i;

	i = 0;
	if (!array || position < 0 || buffer == 0)
		return (0);
	array[position] = malloc(buffer * sizeof(char));
	if (!array[position])
	{
		while (i < position)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
		return (0);
	}
	return (1);
}

static size_t	count_tokens(char const *s, char const *delim)
{
	size_t	tokens;
	int		inside_token;
	char	quote_char;

	tokens = 0;
	inside_token = 0;
	quote_char = 0;
	if (!s)
		return (0);
	while (*s)
	{
		handle_quotes(*s, &quote_char);
		if (!quote_char)
		{
			handle_redirections(&s, &inside_token, &tokens);
			handle_token_count(*s, delim, &inside_token, &tokens);
			s++;
		}
	}
	return (tokens);
}

char	**ft_tokenizer(char const *s, char const *delims)
{
	size_t	tokens;
	char	**split_arr;

	tokens = 0;
	if (!s || !delims)
		return (NULL);
	tokens = count_tokens(s, delims);
	if (tokens < 1)
		return (NULL);
	split_arr = malloc((tokens + 1) * sizeof(char *));
	if (!split_arr)
		return (NULL);
	split_arr[tokens] = NULL;
	if (!fill(split_arr, s, delims))
		return (NULL);
	return (split_arr);
}
