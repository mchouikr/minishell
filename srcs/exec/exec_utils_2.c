/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchouikr <mchouikr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:40:16 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 18:37:42 by mchouikr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup_for_exec(t_command *cmd, t_data *data)
{
	if (cmd->cmd != NULL)
	{
		data->stdin_backup = dup(STDIN_FILENO);
		data->stdout_backup = dup(STDOUT_FILENO);
	}
}

// if infile is invalid
void	handle_file_error(t_command *cmd, t_data *data, t_input *input)
{
	restore_stds(data);
	free_data(data);
	free_command(cmd);
	ft_free(input->parsed);
	free(input);
	exit(1);
}

void	error(char *str, int flag)
{
	if (flag == NO_SUCH_FILE)
		ft_fprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			str);
	if (flag == PERM_DENIED)
		ft_fprintf(STDERR_FILENO, "minishell: %s: Permission denied\n",
			str);
	if (flag == CMD_NOT_FOUND)
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			str);
	if (flag == IS_A_DIRECTORY)
		ft_fprintf(STDERR_FILENO, "minishell: %s: Is a directory\n",
			str);
}

void	free_here(t_command *cmd, t_data *data, t_input *input)
{
	free_data(data);
	free_command(cmd);
	ft_free(input->parsed);
	free(input);
}

char	**get_possible_paths(char **env)
{
	int		i;
	char	**possible_paths;

	possible_paths = NULL;
	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	possible_paths = ft_split(env[i] + 5, ':');
	if (!possible_paths)
		return (NULL);
	return (possible_paths);
}
