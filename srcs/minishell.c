/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:17:22 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/27 20:45:46 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_input		*input;
	t_data		*data;
	t_command	*cmd;

	cmd = NULL;
	if (ac == 1 && av[0])
	{
		input = malloc(sizeof(t_input));
		if (!input)
			return (perror("Failed to allocate input struct\n"),
				exit(EXIT_FAILURE), 1);
		data = malloc(sizeof(t_data));
		if (!data)
			return (perror("Failed to allocate data struct\n"),
				exit(EXIT_FAILURE), 1);
		init_data(data, env);
		while (1)
		{
			prompt(input, data, cmd);
		}
	}
	else
		return (ft_printf("Usage: ./minishell\n"), 1);
	return (data->exit_status);
}
