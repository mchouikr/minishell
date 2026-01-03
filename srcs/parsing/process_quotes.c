/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:41:51 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/21 16:42:42 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	close_quote(int *in_single_quote, int *in_double_quote)
// {
// 	if (*in_single_quote || *in_double_quote)
// 	{
// 		if(*in_single_quote)
// 			ft_fprintf(STDOUT_FILENO, "minishell: \n");
// 		if (*in_double_quote)
// 			ft_fprintf(STDOUT_FILENO,
//"You forgot to closed a double quote so we closed it for you\n");
// 	}
// }

static int	process_quotes(const char *str, char *cleaned_str, int *i, int *j)
{
	int	in_single_quote;
	int	in_double_quote;

	in_double_quote = 0;
	in_single_quote = 0;
	while (str && str[*i])
	{
		if (str[*i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			(*i)++;
			continue ;
		}
		if (str[*i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			(*i)++;
			continue ;
		}
		cleaned_str[(*j)++] = str[(*i)++];
	}
	if (in_single_quote || in_double_quote)
		return (1);
	cleaned_str[*j] = '\0';
	return (0);
}

char	*remove_double_quotes(const char *str, t_command *cmd)
{
	int		len;
	int		i;
	int		j;
	char	*cleaned_str;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(str);
	cleaned_str = malloc(len + 1);
	if (!cleaned_str)
		return (NULL);
	if (process_quotes(str, cleaned_str, &i, &j) != 0)
		cmd->quote_status = 1;
	return (cleaned_str);
}

// static int	process_quotes(const char *str, char *cleaned_str, int *i,
// int *j)
// {
// 	int	in_single_quote;
// 	int	in_double_quote;
// 	char	*line;

// 	in_double_quote = 0;
// 	in_single_quote = 0;
// 	while (str && str[*i])
// 	{
// 		if (str[*i] == '\'' && !in_double_quote)
// 		{
// 			in_single_quote = !in_single_quote;
// 			(*i)++;
// 			continue ;
// 		}
// 		if (str[*i] == '"' && !in_single_quote)
// 		{
// 			in_double_quote = !in_double_quote;
// 			(*i)++;
// 			continue ;
// 		}
// 		cleaned_str[(*j)++] = str[(*i)++];
// 	}
//     while (in_single_quote || in_double_quote)
//     {
//         ft_printf("quote> ");
//         line = get_next_line(STDIN_FILENO);
//         if (!line || g_signal == 1)
// 		{
// 			reset_signal();
//             return (1);
// 		}
//         *i = 0;
//         while (line[*i])
//         {
//             if (line[*i] == '\'' && !in_double_quote)
//             {
//                 in_single_quote = !in_single_quote;
//                 (*i)++;
//                 continue ;
//             }
//             if (line[*i] == '"' && !in_single_quote)
//             {
//                 in_double_quote = !in_double_quote;
//                 (*i)++;
//                 continue ;
//             }
//             cleaned_str[(*j)++] = line[(*i)++];
//         }
//         free(line);
//     }
// 	cleaned_str[*j] = '\0';
// 	return (0);
// }