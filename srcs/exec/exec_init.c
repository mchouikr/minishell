/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:39:44 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 18:53:08 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

char	**copy_and_add_env(char **old_env, char *new_str, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env && old_env[i])
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = new_str;
	new_env[i + 1] = NULL;
	free(old_env);
	return (new_env);
}

char	**update_minimal_env(char *var_name, char *value, t_data *data)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_strjoin(var_name, value);
	if (!new_str)
		return (NULL);
	while (data->mini_env && data->mini_env[i])
	{
		if (!ft_strncmp(data->mini_env[i], var_name, ft_strlen(var_name)))
		{
			free(data->mini_env[i]);
			data->mini_env[i] = new_str;
			return (data->mini_env);
		}
		i++;
	}
	return (copy_and_add_env(data->mini_env, new_str, i));
}

void	store_initial_shlvl(t_data *data)
{
	char	*shlvl_str;

	shlvl_str = getenv("SHLVL");
	if (shlvl_str)
		data->initial_shlvl = ft_atoi(shlvl_str) - 1;
	else
		data->initial_shlvl = 0;
}

void	update_shlvl(t_data *data)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;

	new_shlvl = NULL;
	shlvl_str = getenv("SHLVL");
	shlvl = data->initial_shlvl;
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str);
	shlvl++;
	if (shlvl)
		new_shlvl = ft_itoa(shlvl);
	if (new_shlvl)
		update_minimal_env("SHLVL=", new_shlvl, data);
	free(new_shlvl);
}

void	check_env(t_data *data, char **env, char *cwd)
{
	if (env && *env)
	{
		data->mini_env = ft_tabdup(env);
		if (getenv("PWD") == NULL)
			data->mini_env = update_minimal_env("PWD=", "/", data);
		if (getenv("SHLVL") == NULL)
			data->mini_env = update_minimal_env("SHLVL=", "2", data);
		if (getenv("PATH") == NULL)
			data->mini_env = update_minimal_env("PATH=",
					"/usr/local/bin:/usr/bin:/bin", data);
		if (getenv("_") == NULL)
			data->mini_env = update_minimal_env("_=", "/usr/bin/env", data);
	}
	else
	{
		data->mini_env = malloc(sizeof(char *) * 5);
		if (getcwd(cwd, PATH_MAX) != NULL)
			data->mini_env[0] = ft_strjoin("PWD=", cwd);
		else
			data->mini_env[0] = ft_strdup("PWD=/");
		data->mini_env[1] = ft_strdup("SHLVL=2");
		data->mini_env[2] = ft_strdup("PATH=/usr/local/bin:/usr/bin:/bin");
		data->mini_env[3] = ft_strdup("_=/usr/bin/env");
		data->mini_env[4] = NULL;
	}
}

// static char **update_minimal_env(char *var_name, char *value, t_data *data)
// {
//     char    **new_mini_env;
//     int     i;
//     char    *new_str;

//     i = 0;
//     new_str = ft_strjoin(var_name, value);
//     if (!new_str)
//         return (NULL);
//     while (data->mini_env[i])
//     {
//         if (ft_strncmp(data->mini_env[i], var_name,
// ft_strlen(var_name)) == 0)
//         {
//             free(data->mini_env[i]);
//             data->mini_env[i] = new_str;
//             return (data->mini_env);
//         }
//         i++;
//     }
//     new_mini_env = malloc(sizeof(char *) * (ft_tablen(data->mini_env) + 2));
//     if (!new_mini_env)
//         return (free(new_str), NULL);
//     i = 0;
// 	if(data->mini_env)
// 		while (data->mini_env[i])
// 		{
// 			new_mini_env[i] = data->mini_env[i];
// 			i++;
// 		}
//     new_mini_env[i] = new_str;
//     new_mini_env[i + 1] = NULL;
//     free(data->mini_env);
//     return (new_mini_env);
// }

// void set_mini_env_var(char ***mini_env, const char *name,
// const char *value) {
//     int i = 0;
//     size_t name_len = strlen(name);
//     char *new_var = malloc(name_len + strlen(value) + 2); //
// +2 for '=' and '\0'
//     sprintf(new_var, "%s=%s", name, value);

//     // Search for the variable in mini_env
//     while ((*mini_env)[i]) {
//         if (strncmp((*mini_env)[i], name, name_len) == 0
// && (*mini_env)[i][name_len] == '=') {
//             // Update the existing variable
//             free((*mini_env)[i]);
//             (*mini_env)[i] = new_var;
//             return ;
//         }
//         i++;
//     }

//     // If not found, add the new variable
//     char **new_env = realloc(*mini_env, sizeof(char *) * (i + 2)); //
// +2 for new var and NULL terminator
//     if (!new_env) {
//         free(new_var);
//         return ; // Handle allocation failure
//     }
//     new_env[i] = new_var;
//     new_env[i + 1] = NULL;
//     *mini_env = new_env;
// }
