/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:44:00 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/27 16:46:05 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;
	size_t	name_len;

	name_len = ft_strlen(name);
	new_entry = malloc(name_len + ft_strlen(value) + 2);
	if (!new_entry)
		return (perror("malloc"), NULL);
	ft_strlcpy(new_entry, name, name_len + 1);
	new_entry[name_len] = '=';
	ft_strlcpy(new_entry + name_len + 1, value, ft_strlen(value) + 1);
	return (new_entry);
}

char	**new_env_without_realloc(char **current_env, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (perror("malloc"), NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(current_env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[size + 1] = NULL;
	ft_free(current_env);
	return (new_env);
}

char	**update_env(char **current_env, const char *name, const char *value,
		int overwrite)
{
	int		index;
	char	*new_entry;
	size_t	name_len;

	name_len = ft_strlen(name);
	index = find_env_var(current_env, name, name_len);
	if (current_env[index] && !overwrite)
		return (current_env);
	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (NULL);
	if (current_env[index])
	{
		free(current_env[index]);
		current_env[index] = new_entry;
		return (current_env);
	}
	current_env = new_env_without_realloc(current_env, index);
	if (!current_env)
		return (free(new_entry), NULL);
	current_env[index] = new_entry;
	current_env[index + 1] = NULL;
	return (current_env);
}
