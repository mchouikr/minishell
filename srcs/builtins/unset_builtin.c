/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:19:47 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 15:09:51 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_for_unset(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=' || !(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_command *cmd, t_data *data)
{
	int	arg_index;
	int	var_index;

	if (!data->mini_env || !cmd->args[0])
		return (1);
	if (!cmd->args[1])
		return (0);
	arg_index = 1;
	while (cmd->args[arg_index])
	{
		if (!is_valid_for_unset(cmd->args[arg_index]))
		{
			data->exit_status = 1;
			print_export_error(cmd, cmd->args[arg_index]);
		}
		else
		{
			var_index = get_var_index(cmd, data->mini_env, arg_index);
			if (var_index != -1)
				data->mini_env = unset_values(data->mini_env, var_index);
		}
		arg_index++;
	}
	return (data->exit_status);
}

int	get_var_index(t_command *cmd, char **tab, int arg_index)
{
	int	i;
	int	var_index;

	i = 0;
	var_index = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], cmd->args[arg_index],
				ft_strlen(cmd->args[arg_index])))
			return (var_index = i);
		i++;
	}
	return (-1);
}

char	**unset_values(char **tab, int var_index)
{
	char	**new_tab;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new_tab = malloc(sizeof(char *) * ft_tablen(tab));
	if (!new_tab)
		return (perror("malloc"), NULL);
	while (tab[++i])
	{
		if (i != var_index)
		{
			new_tab[j] = ft_strdup(tab[i]);
			if (!new_tab[j])
			{
				while (--j >= 0)
					free(new_tab[j]);
				return (free(new_tab), perror("malloc"), NULL);
			}
			j++;
		}
	}
	new_tab[j] = NULL;
	return (ft_free(tab), new_tab);
}

// char	**unset_env_values(char **tab, int var_index)
// {
// 	char **new_tab;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	new_tab = malloc(sizeof(char *) * ft_tablen(tab));
//+ 0 because removing a value
// 	if (!new_tab)
// 		return (perror("malloc"), NULL);
// 	while (tab[i])
// 	{
// 		if (i != var_index)
// 		{
// 			new_tab[j] = malloc(sizeof(char) * ft_strlen(tab[i]) + 1);
// 			if (!new_tab)
// 				return (perror("malloc"), NULL);
// 			ft_strlcpy(new_tab[j], tab[i], ft_strlen(tab[i]) + 1);
// 			j++;
// 		}
// 		i++;

// 	}
// 	new_tab[j] = NULL;
// 	return (ft_free(tab), new_tab);
// }

// int	is_valid_for_export_unset(char *str)
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
// 					|| str[i] == '}'  || str[i] == '=' || str[i] == '?')
// 					&& flag % 2 == 0)
// 				return (0);
// 			i++;
// 		}
// 		return (1);
// 	}
// 	else
// 		return (0);
// }