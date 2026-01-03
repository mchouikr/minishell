/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:45:59 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/26 15:57:23 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define COLOR_YELLOW "\001\033[33m\002"
#define COLOR_RESET "\001\033[0m\002"

static int	exit_and_free_prompt(t_command *cmd, t_input *input, t_data *data)
{
	int	exit_code;

	rl_clear_history();
	exit_code = data->exit_status;
	free_data(data);
	free(input);
	free_command(cmd);
	free(cmd);
	return (exit_code);
}

int	prompt(t_input *input, t_data *data, t_command *cmd)
{
	int	exit_code;

	signal_prompt();
	input->rl = readline(COLOR_YELLOW "minishell>: " COLOR_RESET);
	if (!input->rl)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit_code = exit_and_free_prompt(cmd, input, data);
		exit(exit_code);
	}
	if (g_signal == 1)
	{
		data->exit_status = 130;
		g_signal = 0;
	}
	if (ft_strlen(input->rl) != 0)
	{
		add_history(input->rl);
		if (process_input(input, data) != 0)
		{
			return (data->exit_status);
		}
		return (data->exit_status);
	}
	return (data->exit_status);
}
