/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:03:42 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/27 15:04:50 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_export_error(t_command *cmd, char *arg)
{
	int	i;

	i = 1;
	ft_fprintf(STDERR_FILENO, "minishell: %s: `", cmd->args[0]);
	while (cmd->args[i])
	{
		if (cmd->args[1][0] == '-')
		{
			ft_fprintf(STDERR_FILENO, "%c%c' : invalid option\n",
				cmd->args[1][0], cmd->args[1][1]);
			return (2);
		}
		else
		{
			ft_fprintf(STDERR_FILENO, "%s' : not a valid identifier\n", arg);
			if (cmd->args[i + 1] != NULL)
				ft_printf("");
			return (1);
		}
		i++;
	}
	return (0);
}
