/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:44:40 by mchouikr          #+#    #+#             */
/*   Updated: 2026/01/03 11:14:36 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../includes/minishell.h"

enum	e_error
{
	NO_SUCH_FILE = 1,
	PERM_DENIED = 2,
	CMD_NOT_FOUND = 3,
	IS_A_DIRECTORY = 4,
	HEREDOC_WARNING = 5,
};

// child.c
void	child_process(t_command *cmd, t_data *data, t_input *input);
void	dup_and_close_in_child(t_command *cmd, t_data *data);
void	execute_in_child(t_command *cmd, t_data *data, t_input *input,
			int exit_code);
void	ft_execve(t_command *cmd, t_data *data, t_input *input, int exit_code);
void	execute_builtin_in_pipe(t_command *cmd, t_data *data, t_input *input);
int		exit_and_free(t_command *cmd, t_data *data, t_input *input);

// data_init.c
void	init_data(t_data *data, char **env);
void	init_data_2(t_data *data);
void	reinit_data(t_data *data);
void	free_data(t_data *data);

// dup_and_close.c
void	handle_heredoc_no_cmd(t_command *cmd, t_data *data);
void	handle_parent(t_data *data, t_command *cmd, pid_t pid);

// exec_init.c
char	**copy_and_add_env(char **old_env, char *new_str, int size);
char	**update_minimal_env(char *var_name, char *value, t_data *data);
void	store_initial_shlvl(t_data *data);
void	update_shlvl(t_data *data);
void	check_env(t_data *data, char **env, char *cwd);

// exec_utils.c
char	*find_path(char *cmd, char **env, int i);
int		ft_cmd_index(t_command *command);

// exec_utils_2.c
void	dup_for_exec(t_command *cmd, t_data *data);
void	handle_file_error(t_command *cmd, t_data *data, t_input *input);
void	error(char *str, int flag);
void	free_here(t_command *cmd, t_data *data, t_input *input);
char	**get_possible_paths(char **env);

// exec.c
int		execution(t_command *cmd, t_data *data, t_input *input);
void	exec_loop(t_command *command, t_data *data, t_input *input, pid_t pid);
void	wait_for_children(t_data *data, pid_t pid);
void	close_and_wait(t_data *data, pid_t pid);
void	handle_last_process(t_data *data);
int		handle_files(t_command *cmd, t_data *data);

// heredoc.c
void	print_hd_error(int flag);
int		ft_heredoc_loop(char *limiter, t_data *data, int write_fd);
int		ft_heredoc(t_command *cmd, t_data *data);
void	close_heredocs_loop(t_command *cmd);
void	handle_heredoc_global(t_command *cmd, t_data *data, int stdin_backup);
void	end_of_heredoc(char *line, char *limiter);

// is_valid.c
int		is_valid(t_command *cmd, t_data *data, char *path);
int		is_existing(char *cmd, char **env);
int		init_path(t_command *cmd, t_data *data);
int		stat_failed(struct stat filestat, t_command *cmd, t_data *data,
			char *path);

// redirections.c
int		handle_files(t_command *cmd, t_data *data);
int		append_redirect(t_data *data, t_file_data *current);
int		outfile_redirect(t_data *data, t_file_data *current);
int		infile_redirect(t_data *data, t_file_data *current);
int		heredoc_redirect(t_command *cmd, t_data *data);
int		opening_files(t_command *cmd, t_data *data, t_file_data *current);

// single_builtin.c
int		file_single_builtin(t_command *cmd, t_data *data);
void	single_builtin(t_command *cmd, t_data *data, t_input *input);
void	restore_stds(t_data *data);
int		file_mgmt_sg(t_command *cmd, t_data *data, t_file_data *current, int i);
// single_builtin_helper.c
int		infile_redirect_sg(t_data *data, t_file_data *current);
int		heredoc_redirect_sg(t_command *cmd, t_data *data);
int		outfile_redirect_sg(t_data *data, t_file_data *current, int i);
int		append_redirect_sg(t_data *data, t_file_data *current, int i);

#endif // EXEC_H