/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:18:31 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 14:42:06 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// DONE

int	ft_env(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (!data->mini_env)
		return (1);
	if (cmd->args[1] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: %s: No such file or directory\n",
			cmd->args[1]);
		return (127);
	}
	i = 0;
	while (data->mini_env[i])
	{
		ft_fprintf(STDOUT_FILENO, "%s\n", data->mini_env[i]);
		i++;
	}
	return (0);
}
