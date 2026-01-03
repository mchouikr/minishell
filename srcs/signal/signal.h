/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:41:10 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/12 16:53:04 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H
# include <minishell.h>

void					reset_signal(void);
void					signal_prompt(void);
void					exec_signal_sigint(void);
void					heredoc_signals(void);
void					ignore_signal(void);
void					heredoc_signal_helper(int signal);

#endif

// void					exec_signal(void);
// void					exec_signal_sigquit(void);
