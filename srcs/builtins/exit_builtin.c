/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:58:17 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 16:06:22 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_numeric(const char *str)
{
	long long	num;

	num = 0;
	if (ft_strcmp(str, "++") == 0)
		return (0);
	if (ft_strcmp(str, "-9223372036854775808") == 0)
		return (0);
	if (*str == '+' || *str == '-')
	{
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		if (num > (LLONG_MAX - (*str - '0')) / 10)
			return (0);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (1);
}

static int	free_exit(t_input *input, t_data *data, t_command *cmd)
{
	int	exit_code;

	if (input->parsed)
		ft_free(input->parsed);
	free(input);
	rl_clear_history();
	exit_code = data->exit_status;
	restore_stds(data);
	close_heredocs_loop(cmd);
	free_data(data);
	free_command(cmd);
	exit(exit_code);
}

int	is_exit_valid(t_input *input, t_data *data, t_command *cmd)
{
	long long	exit_code;

	if (ft_strcmp(cmd->args[1], "--") == 0)
		exit_code = 0;
	else if (ft_strcmp(cmd->args[1], "-9223372036854775808") == 0)
		exit_code = -9223372036854775807LL - 1;
	else if (!is_numeric(cmd->args[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: numeric argument required\n");
		data->exit_status = 2;
		exit_code = free_exit(input, data, cmd);
		return (exit_code);
	}
	else
		exit_code = ft_atoi(cmd->args[1]);
	return (exit_code);
}

int	ft_exit(t_command *cmd, t_data *data, t_input *input)
{
	long long	exit_code;

	if (cmd->args && cmd->args[1])
	{
		exit_code = is_exit_valid(input, data, cmd);
		data->exit_status = exit_code % 256;
	}
	if (cmd->args && cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		data->exit_status = 1;
		return (data->exit_status);
	}
	exit_code = free_exit(input, data, cmd);
	return (exit_code);
}
