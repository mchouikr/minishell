/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelplan <edelplan@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:41:03 by edelplan          #+#    #+#             */
/*   Updated: 2024/11/27 16:09:08 by edelplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t	g_signal = 0;

void	signal_reset_handler(int signal)
{
	if (signal == SIGQUIT)
		(void)signal;
}

void	reset_signal(void)
{
	(void)signal;
	g_signal = 0;
}

void	sigint_prompt(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 1;
	}
}

void	signal_prompt(void)
{
	if (signal(SIGQUIT, SIG_IGN) != SIG_ERR)
		signal(SIGINT, sigint_prompt);
}

void	heredoc_signal_helper(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 2;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

// void	signal_handler(int signal, siginfo_t *info, void *context)
// {
// 	(void)context;
// 	(void)info;
// 	if (signal == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		if (g_signal_check != 0 || g_signal_check == 1)
// 		{
// 			rl_replace_line("", 0);
// 			// rl_on_new_line();
// 			rl_redisplay();
// 			//close(STDIN_FILENO);
// 		}
// 		else if (g_signal_check != 1 || g_signal_check == 0)
// 		{
// 			rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 		}
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		if (g_signal_check == 1 || g_signal_check != 0)
// 		{
// 			ft_putstr_fd("Quit (Core dumped)\n", STDOUT_FILENO);
// 			// ft_putstr_fd("Quit (Core dumped)\n", STDOUT_FILENO);
// 			// rl_replace_line("", 0);
// 			// rl_on_new_line();
// 			// rl_redisplay();
// 		}
// 		else
// 		{

// 		}
// 		// else if (g_signal_check != 1 || g_signal_check == 0)
// 		// {
// 		// 	rl_replace_line("", 0);
// 		// 	rl_on_new_line();
// 		// 	rl_redisplay();
// 		// 	// close(STDIN_FILENO);
// 		// }
// 	}
// }

// void	signal_handler_ignore(int signal, siginfo_t *info, void *context)
// {
// 	(void)signal;
// 	(void)info;
// 	(void)context;
// 	if (g_signal_check == 0 || g_signal_check != 1)
// 	{
// 			ft_putstr_fd("Quit (Core dumped)\n", STDOUT_FILENO);
// 			rl_on_new_line();
// 			rl_redisplay();
// 	}
// 	//rl_redisplay();
// 	// Do nothing, effectively ignoring the signal
// }

// void	signal_catcher(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = signal_handler;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		perror("sigaction");
// 	// if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 	// 	perror("signal");
// 	if (g_signal_check == 1)
// 	{
// 		sa.sa_sigaction = signal_handler;
// 		sa.sa_flags = SA_RESTART;
// 		if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 			perror("sigaction");
// 	}
// 	if (g_signal_check == 0)
// 	{
// 		sa.sa_handler = SIG_IGN;
// 		if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 			perror("sigaction");
// 	}
// }

// volatile sig_atomic_t	g_signal_check = 0;

// void	signal_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		if (g_signal_check != 0 || g_signal_check == 1)
// 		{
// 			rl_replace_line("", 0);
// 			rl_redisplay();
// 		}
// 		else if (g_signal_check != 1 || g_signal_check == 0)
// 		{
// 			rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 		}
// 	}
// 	else if (signum == SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit (Core dumped)\n", STDOUT_FILENO);
// 		if (g_signal_check != 0 || g_signal_check == 1)
// 		{
// 			rl_replace_line("", 0);
// 			// rl_on_new_line();
// 			rl_redisplay();
// 		}
// 		else if (g_signal_check != 1 || g_signal_check == 0)
// 		{
// 			rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 			// close(STDIN_FILENO);
// 		}
// 	}
// }

// void	signal_handler_ignore(int signal, siginfo_t *info, void *context)
// {
// 	(void)signal;
// 	(void)info;
// 	(void)context;
// 	if (g_signal_check == 0 || g_signal_check != 1)
// 	{
// 			ft_putstr_fd("Quit (Core dumped)\n", STDOUT_FILENO);
// 			rl_on_new_line();
// 			rl_redisplay();
// 	}
// 	//rl_redisplay();
// 	// Do nothing, effectively ignoring the signal
// }

// void	signal_catcher(void)			//close(STDIN_FILENO);
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = &signal_handler;
// 	sa.sa_flags = SA_RESTART;
// 	sigemptyset(&sa.sa_mask);
// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 		perror("sigaction");
// 	// if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 	// 	perror("signal");
// 	// signal(SIGQUIT, SIG_IGN)
// 	if (g_signal_check == 1)
// 	{
// 		sa.sa_handler = signal_handler;
// 		if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 			perror("sigaction");
// 	}
// 	else if (g_signal_check == 0)
// 	{
// 		sa.sa_handler = SIG_IGN;
// 		if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 			perror("sigaction");
// 	}
// }
