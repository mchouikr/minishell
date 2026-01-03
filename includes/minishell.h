/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:31:43 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/27 21:37:07 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/builtins/builtins.h"
# include "../srcs/env/env.h"
# include "../srcs/exec/exec.h"
# include "../srcs/signal/signal.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h> //library for PATH_MAX macro
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# ifndef INPUT_MAX
#  define INPUT_MAX 131072
# endif

extern volatile sig_atomic_t	g_signal;

// minishell_utils

void							ft_free(char **str);
char							*ft_getenv(char **env, char *name);
int								check_fd_limits(t_command *cmd);
void							handle_limiter(t_command *cmd, char *token,
									int *j);
void							handle_append(t_command *cmd, char *token,
									int *m);
void							handle_infile_m(t_command *cmd, char *token,
									int *k);
void							handle_outfile_m(t_command *cmd, char *token,
									int *l);
void							file_management(t_command *cmd, t_input *input);

#endif
