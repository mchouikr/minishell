/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:41:10 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/25 17:20:45 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../front/front.h"
# include <minishell.h>

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				**infile;
	char				**outfile;
	char				**limiter;
	char				**append;
	int					infile_count;
	int					outfile_count;
	int					append_count;
	char				**hd_file_name;
	int					limiter_count;
	int					append_flag;
	int					heredoc;
	int					*heredoc_fds;
	int					quote_status;
	struct s_file_data	*file_data;
	struct s_command	*next;
	struct s_command	*prev;

}						t_command;

typedef struct s_file_data
{
	char				*infile;
	char				*limiter;
	char				*outfile;
	char				*append;
	struct s_file_data	*next;
	struct s_file_data	*prev;
}						t_file_data;
typedef struct s_data
{
	char				**mini_env;
	int					fd[2];
	int					exit_status;
	char				*path;
	char				*program_name;
	int					status;
	int					new_stdin;
	int					new_stdout;
	int					saved_stdin;
	int					saved_stdout;
	int					stdin_backup;
	int					stdout_backup;
	int					heredoc_flag;
	int					single_builtin_flag;
	int					hd_in_pipe;
	int					hd_with_no_cmd;
	int					infile_status;
	int					infile_error_flag;
	int					initial_shlvl;
	size_t				cmd_nbr;
	size_t				childs;
	pid_t				last_pid;
}						t_data;

typedef struct s_input
{
	char				*unparsed;
	char				**parsed;
	char				*rl;
}						t_input;

typedef struct s_parse_data
{
	size_t				len;
	int					beg;
	char				quote_char;
	char				**arr;
}						t_parse_data;

typedef struct s_token_counts
{
	int					arg_count;
	int					in_count;
	int					out_count;
	int					heredoc_count;
	int					append_count;
}						t_token_counts;

// init_and_free.c

int						cmd_fail(t_input *input, t_data *data, t_command *cmd);
int						command_init(t_command *cmd, t_token_counts counts);
void					free_command(t_command *cmd);
void					free_command_single_node(t_command *cmd);
void					cleanup_heredoc_files(t_command *cmd);
void					free_file_data(t_file_data *file_data);
int						init_command_array(t_command *cmd,
							t_token_counts counts);
// minishell.c

int						process_input(t_input *input, t_data *data);
int						prompt(t_input *input, t_data *data, t_command *cmd);

// exec_parsing.c

int						is_exec(char *cmd, char **env);

// token_parsing.c

char					*find_dollar(char *tokens, t_data *data);
t_command				*parse_tokens(char **tokens);
char					*remove_double_quotes(const char *str, t_command *cmd);

// token_parsing_helper.c

int						handle_syntax_error(char *msg);
int						check_initial_syntax(char **tokens);
int						handle_pipe(char **tokens, int i, t_command *cmd);
int						handle_append_redir(char **tokens, int i,
							t_command *cmd);
void					cleanup_cmd(t_command *cmd);
int						handle_basic_redirect(char **tokens, int i,
							t_command *cmd);
void					add_command_and_args(t_command *cmd, char *token,
							int *arg_index);
int						handle_heredoc_redir(char **tokens, int i,
							t_command *cmd);

// builtin_parsing.c

int						exec_builtin(t_command *cmd, t_data *data,
							t_input *input);
int						is_builtin(t_command *cmd);

// input_parsing.c

void					parse_input(t_input *input, t_data *data);

// ft_tokenizer.c

int						fill(char **arr, char const *s, char const *delim);
void					handle_quotes(char c, char *quote_char);
void					handle_token_count(char c, const char *delim,
							int *inside_token, size_t *tokens);
int						safe_malloc(char **array, int position, size_t buffer);
char					**ft_tokenizer(char const *s, char const *delims);
int						handle_redirections(char const **s, int *inside_token,
							size_t *tokens);
char					*find_dollar_heredoc(char *tokens, t_data *data);

// varR_expansion.c

int						handle_quotes_doll(char c, int *in_single,
							int *in_double);

char					*handle_exit_status(char **result, int exit_status,
							int *i);

char					*handle_env_var(char **result, char *tokens, int *i,
							t_data *data);

char					*append_char(char **result, char c);

// char	**input_tokenizer(const char *input);

#endif