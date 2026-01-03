/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:30:13 by mchouikr          #+#    #+#             */
/*   Updated: 2024/11/15 17:55:07 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../../includes/minishell.h"

// typedef struct s_info
// {
// 	int			fd[2];
// 	int			status;
// 	int			exit_status;
// 	char		**mini_env;
// 	char		**export_vars;
// 	size_t		children;
// }				t_info;

// char    *ft_getenv_data(t_our_env *our_env, char *name);
// void	print_our_env (t_our_env *our_env);
// void	parse_env(char **env, t_our_env *our_env);

char	**ft_tabdup(char **src);
int		ft_tablen(char **tab);
#endif