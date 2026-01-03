/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:16:52 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/27 15:30:23 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	file_management_loop(t_command *cmd, t_input *input,
		t_file_data *head)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;

	while (cmd)
	{
		head = cmd->file_data;
		i = 0;
		j = 0;
		k = 0;
		l = 0;
		m = 0;
		while (input->parsed[i])
		{
			handle_limiter(cmd, input->parsed[i], &j);
			handle_append(cmd, input->parsed[i], &m);
			handle_infile_m(cmd, input->parsed[i], &k);
			handle_outfile_m(cmd, input->parsed[i], &l);
			i++;
		}
		cmd->file_data = head;
		cmd = cmd->next;
	}
}

static void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	file_management(t_command *cmd, t_input *input)
{
	t_file_data	*head;
	int			i;

	head = NULL;
	if (!cmd || !input || !cmd->file_data || !input->parsed)
		return ;
	i = 0;
	while (input->parsed[i])
	{
		remove_quotes(input->parsed[i]);
		i++;
	}
	file_management_loop(cmd, input, head);
}
