/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:54:36 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/14 19:34:41 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	allocate_token(char **array, int *start, const char *s, size_t len)
{
	if (!array || !start || !s)
		return (0);
	if (!safe_malloc(array, *start, len + 1))
		return (0);
	if (len > 0)
		ft_strlcpy(array[*start], s - len, len + 1);
	else
		array[*start][0] = '\0';
	(*start)++;
	return (1);
}

static int	handle_single_redirect(t_parse_data *data, char const **s)
{
	if (data->len && !allocate_token(data->arr, &data->beg, *s, data->len))
		return (0);
	if (!safe_malloc(data->arr, data->beg, 2 + 1))
		return (0);
	ft_strlcpy(data->arr[data->beg], *s, 2);
	data->beg++;
	(*s)++;
	data->len = 0;
	return (1);
}

static int	handle_double_redirect(t_parse_data *data, char const **s)
{
	if (data->len && !allocate_token(data->arr, &data->beg, *s, data->len))
		return (0);
	if (!safe_malloc(data->arr, data->beg, 3 + 1))
		return (0);
	ft_strlcpy(data->arr[data->beg], *s, 3);
	data->beg++;
	(*s) += 2;
	data->len = 0;
	return (1);
}

static int	handle_token_parsing(t_parse_data *data, char const **s)
{
	handle_quotes(**s, &data->quote_char);
	if (!data->quote_char && ((**s == '<' && *(*s + 1) == '<') || (**s == '>'
				&& *(*s + 1) == '>')))
		return (handle_double_redirect(data, s));
	if (!data->quote_char && (**s == '<' || **s == '>' || **s == '|'))
		return (handle_single_redirect(data, s));
	data->len++;
	(*s)++;
	return (1);
}

int	fill(char **arr, char const *s, char const *delim)
{
	t_parse_data	data;

	data.len = 0;
	data.beg = 0;
	data.quote_char = 0;
	data.arr = arr;
	while (*s)
	{
		data.len = 0;
		while (ft_strchr(delim, *s) && ft_isspace(*s))
			s++;
		while (*s && (!ft_strchr(delim, *s) || data.quote_char))
			if (!handle_token_parsing(&data, &s))
				return (0);
		if (data.len && !allocate_token(arr, &data.beg, s, data.len))
			return (0);
		if (*s)
			s++;
	}
	arr[data.beg] = NULL;
	return (1);
}

// Allocate delim is now a_d because I hate the norm :')

// static int	a_d(char **array, int *start, const char *s)
// {
// 	if (!safe_malloc(array, *start, 2))
// 		return (0);
// 	array[*start][0] = *s;
// 	array[*start][1] = '\0';
// 	(*start)++;
// 	return (1);
// }

// int	handle_redir(const char **s, char **arr, int *beg, size_t *len)
// {
// 	if (((**s == '<' && *(*s + 1) == '<') || (**s == '>' && *(*s + 1) == '>')))
// 	{
// 		if (*len && !allocate_token(arr, beg, *s, *len))
// 			return (0);
// 		if (!safe_malloc(arr, *beg, 3))
// 			return (0);
// 		ft_strlcpy(arr[*beg], *s, 3);
// 		(*beg)++;
// 		(*s) += 2;
// 		*len = 0;
// 		return (1);
// 	}
// 	if ((**s == '<' || **s == '>'))
// 	{
// 		if (len && !allocate_token(arr, beg, *s, *len))
// 			return (0);
// 		if (!safe_malloc(arr, *beg, 2))
// 			return (0);
// 		ft_strlcpy(arr[*beg], *s, 2);
// 		(*beg)++;
// 		(*s)++;
// 		*len = 0;
// 		return (1);
// 	}
// 	return (0);
// }
// Start is now beg (beginning) because I hate the norm :')

// static	int	handle_double_redirect(char **arr, int *beg, char const **s,
// size_t *len)
// {
// 	if (*len && !allocate_token(arr, &beg, *s, *len))
// 		return (0);
// 	if (!safe_malloc(arr, *beg, 3 + 1))
// 		return (0);
// 	ft_strlcpy(arr[*beg], *s, 3);
// 	(*beg)++;
// 	*s += 2;
// 	*len = 0;
// 	return (1);
// }

// static	int	handle_single_redirect(char **arr, int *beg, char const **s,
// size_t *len)
// {
// 	if (*len && !allocate_token(arr, &beg, *s, *len))
// 		return (0);
// 	if (!safe_malloc(arr, *beg, 2 + 1))
// 		return (0);
// 	ft_strlcpy(arr[*beg], *s, 2);
// 	(*beg)++;
// 	(*s)++;
// 	*len = 0;
// 	return (1);
// }

// static	int	handle_token_parsing(char **ar, char const **s, int *beg,
// size_t *len)

// static int	fill(char **arr, char const *s, char const *delim)
// {
// 	size_t	len;
// 	int		beg;
// 	char	quote_char;

// 	len = 0;
// 	beg = 0;
// 	quote_char = 0;
// 	while (*s)
// 	{
// 		len = 0;
// 		while (ft_strchr(delim, *s) && ft_isspace(*s))
// 			s++;
// 		while (*s && (!ft_strchr(delim, *s) || quote_char))
// 		{
// 			handle_quotes(*s, &quote_char);
// 			if (!quote_char && ((*s == '<' && *(s + 1) == '<') || (*s == '>'
// 						&& *(s + 1) == '>')))
// 			{
// 				if(!handle_double_redirect(arr, &beg, &s, &len))
// 					return (0);
// 				continue ;
// 			}
// 			if (!quote_char && (*s == '<' || *s == '>'))
// 			{
// 				if(!handle_single_redirect(arr, &beg, &s, &len))
// 					return (0);
// 				continue ;
// 			}
// 			len++;
// 			s++;
// 		}
// 		if (len && !allocate_token(arr, &beg, s, len))
// 			return (0);
// 		if (*s && ft_strchr(delim, *s) && !ft_isspace(*s) && !a_d(arr, &beg, s))
// 			return (0);
// 		if (*s)
// 			s++;
// 	}
// 	arr[beg] = NULL;
// 	return (1);
// }
