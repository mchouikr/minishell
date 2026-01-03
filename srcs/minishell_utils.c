/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:48:03 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/28 14:10:37 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getenv(char **env, char *name)
{
	int		i;
	char	*pos;
	long	name_len;

	if (!env)
		return (NULL);
	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		pos = ft_strchr(env[i], '=');
		if (pos)
		{
			if ((pos - env[i]) == name_len && ft_strncmp(env[i], name,
					name_len) == 0)
				return (pos + 1);
		}
		i++;
	}
	return (NULL);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

int	check_fd_limits(t_command *cmd)
{
	t_command	*current;
	int			total_fds;
	int			total_args;
	int			i;

	current = cmd;
	total_fds = 0;
	total_args = 0;
	while (current)
	{
		total_fds += current->infile_count + current->outfile_count
			+ current->limiter_count + current->append_count;
		i = 0;
		while (current->args && current->args[i++])
			total_args++;
		if (total_fds >= MAX_FD || total_args >= (INPUT_MAX / 8) - (8
				* total_args))
		{
			return (ft_fprintf(2, "minishell: Too many arguments or \
file descriptors\n"), 1);
		}
		current = current->next;
	}
	return (0);
}

static int	process_input_error(t_command *cmd, t_input *input)
{
	if (input->parsed)
		ft_free(input->parsed);
	input->parsed = NULL;
	input->unparsed = NULL;
	if (cmd && cmd->quote_status == 1)
		ft_fprintf(STDERR_FILENO, "minishell: quote error\n");
	if (cmd)
		free_command(cmd);
	return (0);
}

// void	print_file_data(t_command *cmd)
// {
// 	t_file_data	*current;
// 	int			cmd_idx;
// 	int			file_idx;

// 	if (!cmd)
// 	{
// 		printf("No commands to display\n");
// 		return ;
// 	}
// 	cmd_idx = 0;
// 	while (cmd)
// 	{
// 		printf("\n=== Command[%d] File Data ===\n", cmd_idx);
// 		if (!cmd->file_data)
// 		{
// 			printf("No file data for this command\n");
// 			cmd = cmd->next;
// 			cmd_idx++;
// 			continue ;
// 		}
// 		current = cmd->file_data;
// 		file_idx = 0;
// 		while (current != NULL)
// 		{
// 			if (current->limiter || current->infile || current->outfile
// 				|| current->append)
// 			{
// 				printf("---File Data[%d]---\n", file_idx);
// 				if (current->limiter)
// 					printf("Limiter: %s\n", current->limiter);
// 				if (current->infile)
// 					printf("Infile: %s\n", current->infile);
// 				if (current->outfile)
// 					printf("Outfile: %s\n", current->outfile);
// 				if (current->append)
// 					printf("Append: %s\n", current->append);
// 				printf("--------------\n");
// 			}
// 			current = current->next;
// 			file_idx++;
// 		}
// 		cmd = cmd->next;
// 		cmd_idx++;
// 	}
// }

int	process_input(t_input *input, t_data *data)
{
	t_command	*cmd;

	input->parsed = NULL;
	parse_input(input, data);
	cmd = parse_tokens(input->parsed);
	file_management(cmd, input);
	if (cmd == NULL || check_fd_limits(cmd) == 1 || cmd->quote_status == 1)
		return (process_input_error(cmd, input), 1);
	if (execution(cmd, data, input) == 1)
		return (process_input_error(cmd, input), 1);
	if (input->parsed)
		ft_free(input->parsed);
	input->parsed = NULL;
	input->unparsed = NULL;
	if (cmd)
		free_command(cmd);
	cmd = NULL;
	reinit_data(data);
	return (0);
}

	// print_cmd(cmd); // DEBUG
		// print_file_data(cmd); // DEBUG

// void	print_parsed_input(char **parsed)
// {
// 	int	i;

// 	i = 0;
// 	printf("---Parsed Input---\n");
// 	if (!parsed)
// 	{
// 		printf("(null)\n");
// 		return ;
// 	}
// 	while (parsed[i])
// 	{
// 		printf("[%d]: '%s'\n", i, parsed[i]);
// 		i++;
// 	}
// 	printf("----------------\n");
// }

// int	check_fd_limits(t_command *cmd)
// {
// 	t_command	*current;
// 	t_command	*start;
// 	static int	total_fds;
// 	static int	total_args;
// 	int			per_cmd_fds;
// 	int			per_cmd_args;

// 	start = cmd;
// 	current = cmd;
// 	total_fds = 0;
// 	total_args = 0;
// 	while (current)
// 	{
// 		per_cmd_fds = current->infile_count + current->outfile_count
// 			+ current->limiter_count;
// 		per_cmd_args = 0;
// 		while (current->args && current->args[per_cmd_args])
// 			per_cmd_args++;
// 		total_fds += per_cmd_fds;
// 		total_args += per_cmd_args;
// 		if (per_cmd_fds >= MAX_FD || total_fds >= MAX_FD
// 			|| per_cmd_args >= (INPUT_MAX / 8) - (8 * per_cmd_args)
// 			|| total_args >= (INPUT_MAX / 8) - (8 * total_args))
// 		{
// 			cmd = start;
// 			return (ft_fprintf(2,
// "minishell: Too many arguments or file descriptors\n"), 1);
// 		}
// 		current = current->next;
// 	}
// 	cmd = start;
// 	return (0);
// }

// 	i = 0;
// 	if (!nb)
// 		return ;
// 	while (nb[i])
// 	{
// 		if (nb[i])
// 			free((int)nb[i]);
// 		nb[i] = 0;
// 		i++;
// 	}
// 	free(nb);
// 	nb = NULL;
// }

// char	*ft_getenv_data(t_our_env *our_env, char *name)
// {
// 	size_t	name_len;

// 	name_len = ft_strlen(name);
// 	while (our_env->next)
// 	{
// 		if ((ft_strncmp(our_env->key, name, name_len) == 0))
// 				return (our_env->data);
// 		our_env = our_env->next;
// 	}
// 	return (NULL);
// }
