/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:28:40 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 20:46:45 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	find_duplicate(t_command *cmd, char **export_values, int arg_index)
{
	int		i;
	char	*key;
	char	*current_key;

	if (!export_values)
		return (-1);
	i = 0;
	while (export_values[i])
	{
		key = ft_substr(cmd->args[arg_index], 0, ft_strchr(cmd->args[arg_index],
					'=') - cmd->args[arg_index]);
		current_key = ft_substr(export_values[i], 0, ft_strchr(export_values[i],
					'=') - export_values[i]);
		if (ft_strcmp(current_key, key) == 0)
		{
			(free(current_key), free(key));
			return (i);
		}
		free(current_key);
		free(key);
		i++;
	}
	return (-1);
}

// 1 if failed, 0 if success

int	ft_export(t_command *cmd, t_data *data)
{
	int	arg_index;
	int	i;

	arg_index = 1;
	if (!cmd->args || !cmd->args[1])
	{
		ft_fprintf(STDERR_FILENO, "No arguments given\n");
		return (1);
	}
	while (cmd->args[arg_index])
	{
		if (!is_valid_for_export(cmd->args[arg_index]))
			data->exit_status = print_export_error(cmd, cmd->args[arg_index]);
		else
		{
			i = find_duplicate(cmd, data->mini_env, arg_index);
			if (i == -1 && ft_strchr(cmd->args[arg_index], '='))
				data->mini_env = export_values_in_env(cmd, data, arg_index);
			if (i >= 0 && ft_strchr(cmd->args[arg_index], '='))
				data->mini_env = expand_existing_env_value(cmd, data, arg_index,
						i);
		}
		arg_index++;
	}
	return (data->exit_status);
}

int	is_valid_for_export(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] != '_') || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	if (i == 0 && str[i] == '=')
		return (0);
	return (1);
}

char	**export_values_in_env(t_command *cmd, t_data *data, int arg_index)
{
	char	**new_mini_env;
	int		i;

	i = 0;
	new_mini_env = malloc(sizeof(char *) * (ft_tablen(data->mini_env) + 2));
	if (!new_mini_env)
		return (perror("malloc"), NULL);
	while (data->mini_env[i])
	{
		new_mini_env[i] = malloc(sizeof(char) * (ft_strlen(data->mini_env[i])
					+ 1));
		if (!new_mini_env[i])
			return (perror("malloc"), NULL);
		ft_strlcpy(new_mini_env[i], data->mini_env[i],
			ft_strlen(data->mini_env[i]) + 1);
		i++;
	}
	new_mini_env[i] = malloc(sizeof(char) * (ft_strlen(cmd->args[1]) + 1));
	if (!new_mini_env[i])
		return (perror("malloc"), NULL);
	ft_strlcpy(new_mini_env[i], cmd->args[arg_index], ft_strlen(cmd->args[1])
		+ 1);
	new_mini_env[i + 1] = NULL;
	ft_free(data->mini_env);
	return (new_mini_env);
}

char	**expand_existing_env_value(t_command *cmd, t_data *data, int arg_index,
		int data_index)
{
	char	**new_mini_env;
	int		i;

	i = 0;
	new_mini_env = ft_tabdup(data->mini_env);
	if (!new_mini_env)
		return (perror("malloc"), NULL);
	while (new_mini_env[i])
	{
		if (i == data_index)
		{
			(free(new_mini_env[i]), new_mini_env[i] = NULL);
			new_mini_env[i] = malloc(sizeof(char)
					* (ft_strlen(cmd->args[arg_index]) + 1));
			if (!new_mini_env[i])
				return (perror("malloc"), NULL);
			ft_strlcpy(new_mini_env[i], cmd->args[arg_index],
				ft_strlen(cmd->args[arg_index]) + 1);
			return (ft_free(data->mini_env), new_mini_env);
		}
		i++;
	}
	ft_free(data->mini_env);
	return (new_mini_env);
}

// char	*normalize_whitespace(char *str)
// {
// 	char *result;
// 	int	i;
// 	int	j;
// 	int	in_whitespace;

// 	result = malloc(ft_strlen(str) + 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	in_whitespace = 0;

// 	while (str[i] && ft_isspace(str[i]))
//         i++;
// 	while(str[i])
// 	{
// 		if(ft_isspace(str[i]))
// 		{
// 			if (!in_whitespace)
// 			{
// 				result[j++] = ' ';
// 				in_whitespace = 1;
// 			}
// 		}
// 		else
// 		{
// 			result[j++] = str[i];
// 			in_whitespace = 0;
// 		}
// 		i++;
// 	}
// 	result[j] = '\0';
// 	while(j > 0 && ft_isspace(result[j - 1]))
// 	{
// 		result[j - 1] = '\0';
// 		j--;
// 	}
// 	return (result);
// }

// int	is_valid_for_export(char *str)
// {
//     int		i;
//     char	*plus_pos;

//     i = 0;
//     if (!str || !*str || ft_isdigit(str[0]))
//         return (0);
//     if (str[0] == '=' || str[0] == '+')
//         return (0);

//     plus_pos = ft_strchr(str, '+');
//     if (plus_pos && plus_pos[1] == '=')
//     {
//         // Check if characters before '+=' are valid
//         while (str != plus_pos)
//         {
//             if (!ft_isalnum(*str) && *str != '_')
//                 return (0);
//             str++;
//         }
//         return (1);
//     }

//     while (str[i] && str[i] != '=')
//     {
//         if (!ft_isalnum(str[i]) && str[i] != '_')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int	is_valid_for_export(char *str)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	flag = 0;
// 	if (ft_isalpha(str[0]) || str[0] == '_')
// 	{
// 		while (str[i])
// 		{
// 			if (str[i] == '=')
// 				flag++;
// 			if ((str[i] == '!' || str[i] == '@' || str[i] == '#'
// 					|| str[i] == '$' || str[i] == '%' || str[i] == '^'
// 					|| str[i] == '&' || str[i] == '*' || str[i] == '-'
// 					|| str[i] == '+' || str[i] == '.' || str[i] == '{'
// 					|| str[i] == '}' ) && flag % 2 == 0)
// 				return (0);
// 			i++;
// 		}
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

// replace
// int has_append_operator(const char *str)
// {
//     char *plus_pos;

//     plus_pos = ft_strchr(str, '+');
//     return (plus_pos && plus_pos[1] == '=');
// }
// //replace
// char *get_append_key(const char *str)
// {
//     char *plus_pos;

//     plus_pos = ft_strchr(str, '+');
//     return (ft_substr(str, 0, plus_pos - str));
// }
// //replace
// char *get_append_value(const char *str)
// {
//     char *eq_pos;

//     eq_pos = ft_strchr(str, '=');
//     return (ft_strdup(eq_pos + 1));
// }

// char *get_existing_value(char **env, const char *key)
// {
//     int i;
//     size_t key_len;

//     i = 0;
//     key_len = 0;
//     while (key[key_len] && key[key_len] != '+' && key[key_len] != '=')
//         key_len++;

//     while (env[i])
//     {
//         if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
//             return (env[i] + key_len + 1);
//         i++;
//     }
//     return (NULL);
// }

// int ft_export(t_command *cmd, t_data *data)
// {
//     int     arg_index;
//     int     i;
//     char    *cleaned_str;
//     char    *key;
//     char    *value;
//     char    *existing_value;
//     char    *new_value;

//     arg_index = 1;
//     if (!cmd->args || !cmd->args[1])
//         return (1);
//     while (cmd->args[arg_index])
//     {
//         if (!is_valid_for_export(cmd->args[arg_index]))
//         {
//             data->exit_status = 1;
//             print_export_error(cmd, cmd->args[arg_index]);
//         }
//         else
//         {
//             cleaned_str = normalize_whitespace(cmd->args[arg_index]);
//             if (!cleaned_str)
//             {
//                 perror("malloc");
//                 data->exit_status = 1;
//                 return (1);
//             }

//             if (has_append_operator(cleaned_str))
//             {
//                 key = get_append_key(cleaned_str);
//                 value = get_append_value(cleaned_str);
//                 existing_value = get_existing_value(data->mini_env, key);

//                 if (existing_value)
//                 {
//                     new_value = ft_strjoin(existing_value, value);
//                     free(cleaned_str);
//                     cleaned_str = ft_strjoin(key, "=");
//                     char *tmp = cleaned_str;
//                     cleaned_str = ft_strjoin(cleaned_str, new_value);
//                     free(tmp);
//                     free(new_value);
//                 }
//                 else
//                 {
//                     free(cleaned_str);
//                     cleaned_str = ft_strjoin(key, "=");
//                     char *tmp = cleaned_str;
//                     cleaned_str = ft_strjoin(cleaned_str, value);
//                     free(tmp);
//                 }
//                 free(key);
//                 free(value);
//             }

//             free(cmd->args[arg_index]);
//             cmd->args[arg_index] = cleaned_str;
//             i = find_duplicate(cmd, data->mini_env, arg_index);
//             if (i == -1 && ft_strchr(cmd->args[arg_index], '='))
//                 data->mini_env = export_values_in_env(cmd, data, arg_index);
//             if (i >= 0 && ft_strchr(cmd->args[arg_index], '='))
//                 data->mini_env = expand_existing_env_value(cmd, data,
//		arg_index, i);
//         }
//         arg_index++;
//     }
//     return (data->exit_status);
// }
