/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:58 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/13 16:39:32 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	return_if_sig(int status, int l)
{
	if (WTERMSIG(status) == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (WTERMSIG(status) == SIGQUIT)
		ft_putstr_fd("QUIT (core dumped)\n", STDOUT_FILENO);
	return (128 + WTERMSIG(status));
}

static void handle_sigint(int sig)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line(); // cursor of readline on a nl so that next input occurs on nl
	rl_replace_line("", 0); //clear current input replacing it with empty string
	rl_redisplay(); // redisplays the prompt and the empty input line
}

/* signal handling for the parent process*/
void	main_signals(void)
{
	struct sigaction sigint;
	struct sigaction sigquit;

	sigint.sa_flags = 0;
	sigint.sa_handler = &handle_sigint;
	//sigint.sa_handler = SIG_DFL;
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = 0;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	execute_signals(int pid)
{
	struct sigaction sig;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (pid == 0)
		sig.sa_handler = SIG_DFL;
	else
		sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

static void heredoc_sigint(int sig)
{
	//int	mem_stdin;

	//mem_stdin = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	//dup(STDIN_FILENO);
 //ft_putstr_fd("\n", STDOUT_FILENO);
//	rl_on_new_line(); // cursor of readline on a nl so that next input occurs on nl
	//rl_replace_line("", 0); //clear current input replacing it with empty string
	//rl_redisplay();
	//dup2(mem_stdin, STDIN_FILENO);
}

void	heredoc_signals(void)
{
	struct sigaction sigint;
	struct sigaction sigquit;
	int	mem_stdin;

	mem_stdin = dup(STDIN_FILENO);
	sigint.sa_flags = 0;
	sigemptyset(&sigint.sa_mask);
	sigquit.sa_flags = 0;
	sigemptyset(&sigquit.sa_mask);
	sigint.sa_handler = &heredoc_sigint;
	sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
	dup2(mem_stdin, STDIN_FILENO);
	//printf("here\n");
}

/*
int		g_signal_count = 0;

void	handle_sigint_interactive(int sig)
{
	g_signal_count++;
	write(2, "\nminishell\% ", 13);
	return ((void)sig);
}

// Gestionnaire pour SIGINT dans un heredoc
void	handle_sigint_heredoc(int sig)
{
	g_signal_count++;
	write(2, "minishell\%", 13);
	return ((void)sig);
}

// Gestionnaire pour SIGINT dans une commande bloquante
void	handle_sigint_command(int sig)
{
	g_signal_count++;
	write(2, "^C\nminishell\% ", 15);
	return ((void)sig);
}

// Gestionnaire pour SIGQUIT dans une commande bloquante
void	handle_sigquit_command(int sig)
{
	g_signal_count++;
	write(2, "Quit (core dumped)\n", 19);
	return ((void)sig);
}

// Gestionnaire pour SIGQUIT qui ne fait rien (utilisé pour mode interactif et heredoc)
void	handle_sigquit(int sig)
{
	return ((void)sig);
}

void	setup_signal_handlers(void (*sigint_handler)(int),
		void (*sigquit_handler)(int))
{
	struct sigaction	sa;

	// Configuration pour SIGINT
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	// Configuration pour SIGQUIT
	sa.sa_handler = sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}
*/
