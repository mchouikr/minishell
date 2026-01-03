/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:49:57 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 18:24:50 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_data(t_data *data, char **env)
{
	char	cwd[PATH_MAX];

	store_initial_shlvl(data);
	check_env(data, env, cwd);
	if (!data->mini_env)
		return (perror("Failed to allocate mini_env\n"), exit(EXIT_FAILURE));
	update_shlvl(data);
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->exit_status = 0;
	data->path = NULL;
	data->status = 0;
	data->new_stdin = -1;
	data->new_stdout = -1;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->stdin_backup = -1;
	data->stdout_backup = -1;
	data->infile_error_flag = 0;
	data->cmd_nbr = 0;
	init_data_2(data);
}

void	init_data_2(t_data *data)
{
	data->childs = 0;
	data->heredoc_flag = 0;
	data->hd_with_no_cmd = 0;
	data->hd_in_pipe = 0;
	data->infile_status = 0;
	data->single_builtin_flag = 0;
	data->last_pid = 0;
	data->program_name = NULL;
}

void	reinit_data(t_data *data)
{
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->path = NULL;
	data->status = 0;
	data->new_stdin = -1;
	data->new_stdout = -1;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->infile_error_flag = 0;
	data->infile_status = 0;
	data->hd_with_no_cmd = 0;
	data->hd_in_pipe = 0;
	data->cmd_nbr = 0;
	data->childs = 0;
	data->single_builtin_flag = 0;
	data->heredoc_flag = 0;
	data->last_pid = 0;
}

void	free_data(t_data *data)
{
	if (data->mini_env)
		ft_free(data->mini_env);
	data->fd[0] = 0;
	data->fd[1] = 0;
	data->exit_status = 0;
	if (data->path)
		free(data->path);
	data->path = NULL;
	data->status = 0;
	data->new_stdin = 0;
	data->new_stdout = 0;
	data->saved_stdin = 0;
	data->saved_stdout = 0;
	data->infile_error_flag = 0;
	data->infile_status = 0;
	data->hd_in_pipe = 0;
	data->hd_with_no_cmd = 0;
	data->cmd_nbr = 0;
	data->childs = 0;
	data->single_builtin_flag = 0;
	data->heredoc_flag = 0;
	data->last_pid = 0;
	free(data);
}
