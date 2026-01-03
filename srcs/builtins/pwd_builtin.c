/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:44:36 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 17:04:46 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
		ft_printf("%s\n", path);
	else
		perror("pwd error");
}

// DONE

// int	pwd_checks(t_command *cmd)
// {
// 	if (!cmd->args[1])
// 		return (0);
// 	else
// 	{
// 		if (cmd->args[1][0] == '-')
// 		{
// 			if (ft_isprint(cmd->args[1][1]))
// 			{
// 				return (printf("minishell: pwd: %c%c: invalid option\n",
// 					cmd->args[1][0], cmd->args[1][1]), 1);
// 			}
// 			else
// 				return (0);
// 		}
// 		else
// 			return (0);
// 	}
// 	return (1);
// }
