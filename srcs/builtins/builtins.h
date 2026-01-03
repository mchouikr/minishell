/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:59:04 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 16:56:56 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../env/env.h"
# include <minishell.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

void	ft_pwd(void);
int		ft_env(t_command *cmd, t_data *data);

// cd_builtin.c
char	*get_pwd(void);
char	**update_env(char **curent_env, const char *name, const char *value,
			int overwrite);
int		ft_cd(const char *path, t_data *data);
char	*create_env_entry(const char *name, const char *value);
char	**new_env_without_realloc(char **current_env, int size);

// export_builtin.c
int		ft_export(t_command *cmd, t_data *data);
int		find_duplicate(t_command *cmd, char **export_values, int arg_index);
char	**expand_existing_env_value(t_command *cmd, t_data *data, int arg_index,
			int data_index);
char	**export_values_in_env(t_command *cmd, t_data *data, int arg_index);
int		find_env_var(char **env, const char *name, size_t name_len);

// export_builtin_utils.c
int		print_export_error(t_command *cmd, char *arg);
int		is_valid_for_export(char *str);

// unset_builtin.c
int		ft_unset(t_command *cmd, t_data *data);
char	**unset_values(char **tab, int var_index);
int		get_var_index(t_command *cmd, char **tab, int arg_index);

int		ft_echo(t_command *cmd, t_data *data);
int		ft_exit(t_command *cmd, t_data *data, t_input *input);

#endif // BUILTINS_H