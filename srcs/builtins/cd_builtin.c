/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:31:16 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 16:56:39 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// V1 DONE
// Need to:
//- change relative or absolute directory
//- update old pwd env value
//- update pwd env value
//-

int	find_env_var(char **env, const char *name, size_t name_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*get_pwd(void)
{
	char	path[PATH_MAX];
	char	*current_pwd;

	ft_memset(path, 0, PATH_MAX);
	if (getcwd(path, sizeof(path)) != NULL)
	{
		current_pwd = ft_strdup(path);
		if (!current_pwd)
			return (ft_fprintf(STDERR_FILENO, \
"malloc of current_pwd for cd failed"), NULL);
		return (current_pwd);
	}
	else
		return (ft_fprintf(STDERR_FILENO, \
"cd: error retrieving current directory\n"), NULL);
}

static int	validate_path(const char *target_dir, const char *path)
{
	struct stat	path_stat;

	if (stat(target_dir, &path_stat) != 0)
	{
		return (ft_fprintf(STDERR_FILENO, "minishell: cd: \
%s: No such file or directory\n", path), 1);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		return (ft_fprintf(STDERR_FILENO, "minishell: cd: \
%s: Not a directory\n", path), 1);
	}
	return (0);
}

static int	update_pwd_vars(t_data *data, const char *target_dir)
{
	char	*temp_pwd;

	temp_pwd = get_pwd();
	if (temp_pwd == NULL)
		return (1);
	data->mini_env = update_env(data->mini_env, "OLDPWD", temp_pwd, -1);
	free(temp_pwd);
	if (chdir(target_dir) != 0)
		return (ft_fprintf(STDERR_FILENO, "minishell: cd: \
%s: No such file or directory\n", target_dir), 1);
	temp_pwd = get_pwd();
	data->mini_env = update_env(data->mini_env, "PWD", temp_pwd, -1);
	free(temp_pwd);
	return (0);
}

int	ft_cd(const char *path, t_data *data)
{
	const char	*target_dir;
	char		*dup_path;
	int			ret;

	dup_path = NULL;
	if (!path)
		return (ft_fprintf(STDERR_FILENO, "No absolute \
or relative path\n"), 1);
	dup_path = ft_strdup(path);
	target_dir = dup_path;
	ret = validate_path(target_dir, path);
	if (ret != 0)
	{
		free(dup_path);
		return (ret);
	}
	ret = update_pwd_vars(data, target_dir);
	free(dup_path);
	return (ret);
}

// int		find_env_var(char **current_env, const char *name, )
// {
// 	int	i;

// 	i = 0;
// 	while (current_env[i])
// 	{
// 		if (ft_strncmp(current_env[i], name, name_len) == 0
// 			&& current_env[i][name_len] == '=')
// 		{
// 			if (!overwrite)
// 				return (current_env);
// 			free(current_env[i]);
// 			break ;
// 		}
// 		i++;
// 	}
// }

// char	**update_env(char **current_env, const char *name, const char *value,
// 		int overwrite)
// {
// 	int		i;
// 	size_t	name_len;
// 	char	*new_entry;

// 	name_len = ft_strlen(name);

// 	new_entry = malloc(name_len + ft_strlen(value) + 2);
// 	if (!new_entry)
// 		return (perror("malloc"), NULL);
// 	ft_strlcpy(new_entry, name, name_len + 1);
// 	new_entry[name_len] = '=';
// 	ft_strlcpy(new_entry + name_len + 1, value, ft_strlen(value) + 1);
// 	if (current_env[i])
// 		current_env[i] = new_entry;
// 	else
// 	{
// 		current_env = new_env_without_realloc(current_env, i);
// 		if (!current_env)
// 			return (perror("realloc"), NULL);
// 		current_env[i] = new_entry;
// 		current_env[i + 1] = NULL;
// 	}
// 	return (current_env);
// }

// 	else
// 	{
// 		dup_path = ft_strdup(path);
// 		target_dir = dup_path;
// 	}
// 	if (stat(target_dir, &path_stat) != 0)
// 	{
// 		free(dup_path);
// return (ft_fprintf(STDERR_FILENO, "minishell: cd:
// %s: No such file or directory\n", path), 1);
// 	}
// 	if (!S_ISDIR(path_stat.st_mode))
// 	{
// 		free(dup_path);
// 		return (ft_fprintf(STDERR_FILENO, "minishell: cd:
// %s: Not a directory\n", path), 1);
// 	}
// 	temp_pwd = get_pwd();
// 	if (temp_pwd == NULL)
// 		return (1);
// 	data->mini_env = update_env(data->mini_env, "OLDPWD", temp_pwd, -1);
// 	free(temp_pwd);
// 	if (chdir(target_dir) != 0)
// 		return (ft_fprintf(STDERR_FILENO, "minishell: cd:
// %s: No such file or directory\n", path), 1);
// 	temp_pwd = get_pwd();
// 	data->mini_env = update_env(data->mini_env, "PWD", temp_pwd, -1);
// 	free(dup_path);
// 	free(temp_pwd);
// 	return (0);
// }

// char	**update_env(char **current_env, char *name, const char *temp_pwd,
// 		int i)
// {
// 	char	**new_env;

// 	i = -1;
// 	new_env = malloc(sizeof(char *) * (ft_tablen(current_env) + 1));
// 	if (!new_env)
// 		return (perror("cd new_env malloc failed"), exit(EXIT_FAILURE), NULL);
// 	while (++i < ft_tablen(current_env))
// 	{
// 		if (!(ft_strnstr(current_env[i], name, ft_strlen(name))))
// 		{
// 			new_env[i] = ft_strdup(current_env[i]); //malloc(sizeof(char)
//	* (ft_strlen(current_env[i]) + 1));
// 			if (!new_env[i])
// 				return (ft_free(new_env), perror("cd new_env malloc failed"),
// 					exit(EXIT_FAILURE), NULL);
// 			// ft_strlcpy(new_env[i], current_env[i], ft_strlen(current_env[i])
// 			// 	+ 1);
// 		}
// 		else if (ft_strnstr(current_env[i], name, ft_strlen(name)))
// 		{
// 			new_env[i] = malloc(sizeof(char) * (ft_strlen(name))
// 						+ (ft_strlen(temp_pwd)) + 1);
// 			if (!new_env[i])
// 				return (ft_free(new_env), perror("cd new_env malloc failed"),
// 					exit(EXIT_FAILURE), NULL);
// 			ft_strlcpy(new_env[i], name, ft_strlen(name) + 1);
// 			ft_strlcpy(new_env[i] + ft_strlen(name), temp_pwd, ft_strlen(name)
// 				+ ft_strlen(temp_pwd) + 1);
// 		}
// 	}
// 	return (ft_free(current_env), new_env[i] = NULL, new_env);
// }
