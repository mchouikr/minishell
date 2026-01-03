/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:51:07 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/26 20:14:37 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_quotes_doll(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !*in_double)
	{
		*in_single = !*in_single;
		return (1);
	}
	if (c == '\"' && !*in_single)
	{
		*in_double = !*in_double;
		return (1);
	}
	return (0);
}

char	*handle_exit_status(char **result, int exit_status, int *i)
{
	char	*tmp;
	char	*itoa;

	itoa = ft_itoa(exit_status);
	tmp = ft_strjoin(*result, itoa);
	free(itoa);
	free(*result);
	*i += 2;
	return (tmp);
}

char	*handle_env_var(char **result, char *tokens, int *i, t_data *data)
{
	char	*tmp;
	char	*key;
	char	*expand_value;
	int		j;

	j = *i + 1;
	while (tokens[j] && (ft_isalnum(tokens[j]) || tokens[j] == '_'))
		j++;
	key = ft_substr(tokens, *i + 1, j - (*i + 1));
	expand_value = ft_getenv(data->mini_env, key);
	free(key);
	if (expand_value)
		tmp = ft_strjoin(*result, expand_value);
	else
		tmp = ft_strjoin(*result, "");
	free(*result);
	*i = j;
	return (tmp);
}

char	*append_char(char **result, char c)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(*result, str);
	free(*result);
	return (tmp);
}
