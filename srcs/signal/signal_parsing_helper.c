/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parsing_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:12:16 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/14 11:18:13 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_signal_helper(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		g_signal = 0;
	}
}

void	ignore_signal_help(int signal)
{
	(void)signal;
}

void	ignore_signal(void)
{
	signal(SIGINT, ignore_signal_help);
	signal(SIGQUIT, ignore_signal_help);
}

void	exec_signal_sigint(void)
{
	signal(SIGINT, exec_signal_helper);
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_helper);
	signal(SIGQUIT, SIG_IGN);
}

// void	exec_signal_sigquit(void)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	g_signal = 3;
// }

// void	ignore_signal(void)
// {
// 	struct sigaction sa;

// 	sa.sa_handler = exec_signal_helper;
// 	sigemptyset(&sa.sa_mask);
// 	//sa.sa_flags = SA_NOCLDSTOP;

// 	//sigaction(SIGCHLD, &sa, NULL);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 	// signal(SIGINT, exec_signal_helper);
// 	// signal(SIGQUIT, exec_signal_helper);
// }

// void	exec_signal(void)
// {
// 	if (signal(SIGINT, exec_signal_helper) != SIG_ERR)
// 		signal(SIGQUIT, exec_signal_helper);
// 	g_signal = 3;
// }
