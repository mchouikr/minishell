/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:44:36 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 16:02:09 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// V3 NEED TESTING, handles multiple -n
// voir poour les double quotes etc... comment
// gerer ca: echo "exemple" imprime seulement exeemple sans les ""

void	print_echo(t_command *cmd, int i, int flag)
{
	int	j;

	j = 0;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j])
		{
			write(1, &cmd->args[i][j], 1);
			j++;
		}
		if (cmd->args[i][0] != '\0' && cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 1)
		write(1, "\n", 1);
}

int	ft_echo(t_command *cmd, t_data *data)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 1;
	if (cmd && cmd->args && !cmd->args[1])
		return (ft_printf("\n"), 0);
	while (cmd->args[i] && cmd->args[i][0] == '-' && cmd->args[i][1] == 'n')
	{
		j = 2;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] != '\0')
			break ;
		i++;
		flag = 0;
	}
	print_echo(cmd, i, flag);
	i = 1;
	flag = 1;
	data->exit_status = 0;
	return (data->exit_status);
}
