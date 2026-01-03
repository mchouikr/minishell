/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:39:18 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/25 19:12:42 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_dollar_heredoc(char *tokens, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (tokens[i] != '\0')
	{
		if (tokens[i] == '$')
		{
			if (tokens[i + 1] == '?')
				result = handle_exit_status(&result, data->exit_status, &i);
			else if (tokens[i + 1] && (ft_isalpha(tokens[i + 1]) || tokens[i
						+ 1] == '_'))
				result = handle_env_var(&result, tokens, &i, data);
		}
		else
			result = append_char(&result, tokens[i++]);
	}
	return (result);
}

static char	*process_dollar(char *result, char *tokens, int *i, t_data *data)
{
	if (tokens[*i + 1] == '?')
		return (handle_exit_status(&result, data->exit_status, i));
	if (tokens[*i + 1] && (ft_isalpha(tokens[*i + 1]) || tokens[*i + 1] == '_'))
		return (handle_env_var(&result, tokens, i, data));
	return (append_char(&result, tokens[(*i)++]));
}

char	*find_dollar(char *tokens, t_data *data)
{
	int		i;
	char	*result;
	int		in_single;
	int		in_double;

	in_single = 0;
	in_double = 0;
	i = 0;
	result = ft_strdup("");
	if (tokens[i] == '\'' && tokens[ft_strlen(tokens) - 1] == '\'')
	{
		free(result);
		return (ft_strdup(tokens));
	}
	while (tokens[i])
	{
		if (handle_quotes_doll(tokens[i], &in_single, &in_double))
			result = append_char(&result, tokens[i++]);
		else if (tokens[i] == '$' && !in_single)
			result = process_dollar(result, tokens, &i, data);
		else
			result = append_char(&result, tokens[i++]);
	}
	return (result);
}

// char	*find_dollar_heredoc(char *tokens, t_data *data)
// {
// 	int		i;
// 	char	*result;
// 	char	*expand_value;
// 	char	*tmp;
// 	char	*itoa;
// 	char	*key;
// 	char	str[2];
// 	int		j;

// 	i = 0;
// 	result = ft_strdup("");
// 	while (tokens[i] != '\0')
// 	{
// 		if (tokens[i] == '$')
// 		{
// 			if (tokens[i + 1] == '?')
// 			{
// 				itoa = ft_itoa(data->exit_status);
// 				tmp = ft_strjoin(result, itoa);
// 				free(itoa);
// 				free(result);
// 				result = tmp;
// 				i += 2;
// 				continue ;
// 			}
// 			else if (tokens[i + 1] && (ft_isalnum(tokens[i + 1]) || tokens[i
//					+ 1] == '_'))
// 			{
// 				if (ft_isdigit(tokens[i +1]))
// 				{
// 					i += 2;
// 					continue ;
// 				}
// 				j = i + 1;
// 				while (tokens[j] && (ft_isalnum(tokens[j]) || tokens[j] == '_'))
// 					j++;
// 				key = ft_substr(tokens, i + 1, j - (i + 1));
// 				expand_value = ft_getenv(data->mini_env, key);
// 				free (key);
// 				if (expand_value)
// 				{
// 					tmp = ft_strjoin(result, expand_value);
// 					free(result);
// 				}
// 				else
// 				{
// 					tmp = ft_strjoin(result, "");
// 					free(result);
// 				}
// 				result = tmp;
// 				i = j;
// 				continue ;
// 			}
// 		}
// 		str[0] = tokens[i];
// 		str[1] = '\0';
// 		tmp = ft_strjoin(result, str);
// 		free(result);
// 		result = tmp;
// 		i++;
// 	}
// 	return (result);
// }

// char	*find_dollar(char *tokens, t_data *data)
// {
// 	int		i;
// 	char	*result;
// 	char	*expand_value;
// 	char	*tmp;
// 	char	*key;
// 	char	*itoa;
// 	char	str[2];
// 	int		len;
// 	int		j;
// 	int		in_single_quote;
// 	int		in_double_quote;

// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	len = ft_strlen(tokens);
// 	i = 0;
// 	result = ft_strdup("");
// 	if (tokens[i] == '\'' && tokens[len - 1] == '\'')
// 		return (ft_strdup(tokens));
// 	while (tokens[i] != '\0')
// 	{
// 		if (tokens[i] == '\'' && !in_double_quote)
// 		{
// 			in_single_quote = !in_single_quote;
// 			str[0] = tokens[i];
// 			str[1] = '\0';
// 			tmp = ft_strjoin(result, str);
// 			free(result);
// 			result = tmp;
// 			i++;
// 			continue ;
// 		}
// 		else if (tokens[i] == '\"' && !in_single_quote)
// 		{
// 			in_double_quote = !in_double_quote;
// 			str[0] = tokens[i];
// 			str[1] = '\0';
// 			tmp = ft_strjoin(result, str);
// 			free(result);
// 			result = tmp;
// 			i++;
// 			continue ;
// 		}
// 		if (tokens[i] == '$' && !in_single_quote)
// 		{
// 			if (tokens[i + 1] == '?')
// 			{
// 				itoa = ft_itoa(data->exit_status);
// 				tmp = ft_strjoin(result, itoa);
// 				free(itoa);
// 				free(result);
// 				result = tmp;
// 				i += 2;
// 				continue ;
// 			}
// 			else if (tokens[i + 1] && (ft_isalpha(tokens[i + 1]) || tokens[i
//					+ 1] == '_'))
// 			{
// 				j = i + 1;
// 				while (tokens[j] && (ft_isalnum(tokens[j]) || tokens[j] == '_'))
// 					j++;
// 				key = ft_substr(tokens, i + 1, j - (i + 1));
// 				expand_value = ft_getenv(data->mini_env, key);
// 				free (key);
// 				if (expand_value)
// 				{
// 					tmp = ft_strjoin(result, expand_value);
// 					free(result);
// 				}
// 				else
// 				{
// 					tmp = ft_strjoin(result, "");
// 					free(result);
// 				}
// 				result = tmp;
// 				i = j;
// 				continue ;
// 			}
// 		}
// 		str[0] = tokens[i];
// 		str[1] = '\0';
// 		tmp = ft_strjoin(result, str);
// 		free(result);
// 		result = tmp;
// 		i++;
// 	}
// 	return (result);
// }
