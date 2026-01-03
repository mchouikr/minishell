/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:48:43 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/27 14:30:00 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	process_tokens(t_input *input, t_data *data)
{
	int		i;
	char	*new_token;

	i = 0;
	while (input->parsed[i])
	{
		new_token = find_dollar(input->parsed[i], data);
		free(input->parsed[i]);
		input->parsed[i] = new_token;
		i++;
	}
}

static void	clean_exit_parsing(char **split_res, t_input *input)
{
	perror("Failed to allocated parsed_args\n");
	ft_free(split_res);
	free(input->unparsed);
	exit(EXIT_FAILURE);
}

static char	**init_input_parsing(t_input *input)
{
	char	*tmp;
	char	**split_res;

	if (!input->rl)
		return (NULL);
	tmp = ft_strdup(input->rl);
	if (!tmp)
		return (NULL);
	input->unparsed = tmp;
	free(input->rl);
	split_res = ft_tokenizer(input->unparsed, " \n\t\f\r");
	if (!split_res)
	{
		free(input->unparsed);
		return (NULL);
	}
	return (split_res);
}

void	parse_input(t_input *input, t_data *data)
{
	int		i;
	int		amount_of_cells;
	char	**split_res;

	split_res = init_input_parsing(input);
	if (!split_res)
		return ;
	amount_of_cells = 0;
	while (split_res[amount_of_cells] != NULL)
		amount_of_cells++;
	input->parsed = (char **)ft_calloc(amount_of_cells + 1, sizeof(char *));
	if (!input->parsed)
		clean_exit_parsing(split_res, input);
	i = 0;
	while (i < amount_of_cells)
	{
		input->parsed[i] = ft_strdup(split_res[i]);
		if (!input->parsed[i])
			clean_exit_parsing(split_res, input);
		i++;
	}
	input->parsed[i] = NULL;
	free(input->unparsed);
	ft_free(split_res);
	process_tokens(input, data);
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
// + 1] == '_'))
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
// + 1] == '_'))
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
// line 130 before the j = i + 1;
// if (ft_isdigit(tokens[i +1]))
// {
// 	i += 2;
// 	continue ;
// }				// if (ft_isdigit(tokens[i +1]))
// {
// 	i += 2;
// 	continue ;
// }

// char	*find_dollar(char *tokens, t_data *data)
// {
// 	int		i;
// 	char	*result;
// 	char	*tmp;
// 	char	*env_value;
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
// 				tmp = ft_strjoin(result, ft_itoa(data->exit_status));
// 				free(result);
// 				result = tmp;
// 				i += 2;
// 				continue ;
// 			}
// 			else if (tokens[i + 1] && (ft_isalnum(tokens[i + 1]) || tokens[i
// 						+ 1] == '_'))
// 			{
// 				if (ft_isdigit(tokens[i + 1]))
// 				{
// 					i += 2;
// 					continue ;
// 				}
// 				j = i + 1;
// 				while (tokens[j] && (ft_isalnum(tokens[j]) || tokens[j] == '_'))
// 					j++;
// 				env_value = ft_getenv(data->mini_env, ft_substr(tokens, i + 1, j
// 							- (i + 1)));
// 				if (env_value)
// 					tmp = ft_strjoin(result, env_value);
// 				else
// 					tmp = ft_strjoin(result, "");
// 				free(result);
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

// void	remove_double_quotes_helper(char *cleaned_str, const char *str)
// {
// 	int	i;
// 	int	j;
// 	int	in_single_quote;
// 	int	in_double_quote;

// 	i = 0;
// 	j = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && !in_double_quote)
// 		{
// 			in_single_quote = !in_single_quote;
// 			i++;
// 			continue ;
// 		}
// 		if (str[i] == '"' && !in_single_quote)
// 		{
// 			in_double_quote = !in_double_quote;
// 			i++;
// 			continue ;
// 		}
// 		cleaned_str[j++] = str[i++];
// 	}
// }

// char	*remove_double_quotes(const char *str)
// {
// 	int		len;
// 	int		i;
// 	int		j;
// 	int		in_single_quote;
// 	int		in_double_quote;
// 	char	*cleaned_str;

// 	i = 0;
// 	j = 0;
// 	in_single_quote = 0;
// 	in_double_quote = 0;
// 	len = ft_strlen(str);
// 	cleaned_str = malloc(len + 1);
// 	if (!cleaned_str)
// 		return (NULL);
// 	remove_double_quotes_helper(cleaned_str, str);
// 	cleaned_str[ft_strlen(cleaned_str)] = '\0';
// 	return (cleaned_str);
// }

// void	parse_input_helper(t_input *input, t_data *data, char **split_res,
// 		int amount_of_cells)
// {
// 	int		i;
// 	char	*new_token;

// 	i = -1;
// 	while (++i < amount_of_cells)
// 		input->parsed[i] = ft_strdup(split_res[i]);
// 	free(input->unparsed);
// 	ft_free(split_res);
// 	i = 0;
// 	while (input->parsed[i])
// 	{
// 		new_token = find_dollar(input->parsed[i], data);
// 		free(input->parsed[i]);
// 		input->parsed[i] = new_token;
// 		i++;
// 	}
// }

// void	parse_input(t_input *input, t_command *cmd, t_data *data)
// {
// 	int		amount_of_cells;
// 	char	**split_res;

// 	cmd->exit_status = 0;
// 	amount_of_cells = 0;
// 	if (input->rl == NULL)
// 		return ;
// 	input->unparsed = ft_strdup(input->rl);
// 	free(input->rl);
// 	split_res = ft_tokenizer(input->unparsed, " \n\t\f\r>|<");
// 	if (!split_res)
// 		return ;
// 	while (split_res[amount_of_cells] != NULL)
// 		amount_of_cells++;
// 	input->parsed = (char **)ft_calloc(amount_of_cells + 1, sizeof(char *));
// 	if (!input->parsed)
// 	{
// 		perror("Failed to allocated parsed_args\n");
// 		ft_free(split_res);
// 		exit(EXIT_FAILURE);
// 	}
// 	parse_input_helper(input, data, split_res, amount_of_cells);
// }

// char	*remove_double_quotes(const char *str)
// {
// 	int		len;
// 	int		i;
// 	int		j;
// 	char	*cleaned_str;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(str);
// 	// if ((str[0] == '"' && str[len - 1] == '"'))
// 	// {
// 	// 	str++;
// 	// 	len = ft_strlen(str) - 1;
// 	// }
// 	// else
// 		len = ft_strlen(str);
// 	cleaned_str = malloc(len + 1);
// 	if (!cleaned_str)
// 		return (NULL);
// 	if (str[0] != '\'' && str[len - 1] != '\'')
// 	{
// 		while (str[i])
// 		{
// 			if (str[i] == '"')
// 			{
// 				i ++;
// 				continue ;
// 			}
// 			cleaned_str[j++] = str[i++];
// 		}
// 		cleaned_str[j] = '\0';
// 	}
// 	else if (str[0] == '\'' && str[len - 1] == '\'')
// 	{
// 		while(str[i])
// 		{
// 			if (str[i] == '\'')
// 			{
// 				i++;
// 				continue ;
// 			}
// 			cleaned_str[j++] = str[i++];
// 		}
// 		cleaned_str[j] = '\0';
// 	}
// 	return (cleaned_str);
// }
