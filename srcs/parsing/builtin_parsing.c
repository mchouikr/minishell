/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:43:18 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/25 20:36:03 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(t_command *cmd)
{
	if (!cmd)
		return (0);
	if (cmd->cmd == NULL)
		return (0);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

static void	ft_cd_helper(t_command *cmd, t_data *data)
{
	const char	*path;

	if (cmd && cmd->args)
	{
		if (!cmd->args[1] || cmd->args[1][0] == '~')
			path = getenv("HOME");
		else if (cmd->args[2])
		{
			ft_fprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
			data->exit_status = 1;
			return ;
		}
		else
			path = cmd->args[1];
		if (!path)
		{
			ft_fprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
			data->exit_status = 1;
		}
		else
			data->exit_status = ft_cd(path, data);
	}
}

// returns 0 if failed, 1 if succeed
int	exec_builtin(t_command *cmd, t_data *data, t_input *input)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
	{
		if (ft_echo(cmd, data) == 1)
			return (1);
	}
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd_helper(cmd, data);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		data->exit_status = ft_export(cmd, data);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		data->exit_status = ft_unset(cmd, data);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		data->exit_status = ft_env(cmd, data);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd, data, input);
	else
		return (1);
	return (0);
}
