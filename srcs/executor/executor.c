/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:43:54 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/13 17:45:41 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipes(t_data *shell)
{
	int	i;

	i = 0;
	while (i < (shell->nb_cmd - 1))
	{
		if (pipe(shell->pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

void	fork_cmd(t_data *shell)
{
	int		i;
	int		j;
	t_exec	*current_cmd;
	pid_t	pid;

	i = 0;
	current_cmd = shell->exec;
	while (current_cmd != NULL)
	{
		pid = fork();
		execute_signals(pid);
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			dup_pipe_child(shell, current_cmd, &i);
		else
			current_cmd->pid = pid;
		current_cmd = current_cmd->next;
		i++;
	}
}

void	dup_pipe_child(t_data *shell, t_exec *cmd, int *i)
{
	int	j;

	if (*i < shell->nb_cmd - 1)
		safe_dup2(shell->pipe_fds[*i * 2 + 1], STDOUT_FILENO, shell);
	if (*i > 0)
		safe_dup2(shell->pipe_fds[(*i - 1) * 2], STDIN_FILENO, shell);
	j = -1;
	while (++j < 2 * (shell->nb_cmd - 1))
		close(shell->pipe_fds[j]);
	exec_cmd(shell, cmd);
	exit_free(shell, EXIT_FAILURE);
}

void	close_wait(t_data *shell)
{
	t_exec	*current_cmd;
	int		i;
	int		status;

	i = 0;
	current_cmd = shell->exec;
	while (i < 2 * (shell->nb_cmd - 1))
		close(shell->pipe_fds[i++]);
	while (current_cmd)
	{
		waitpid(current_cmd->pid, &status, 0);
		shell->last_return_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			shell->last_return_code = return_if_sig(status, shell->last_return_code);
		current_cmd = current_cmd->next;
	}
	if (shell->pipe_fds)
		free(shell->pipe_fds);
	shell->pipe_fds = NULL;
}

int	special_built(t_exec *cmd, t_data *shell)
{
	char	**f;

	if (cmd->next)
		return (0);
	shell->spec_built = TRUE;
	f = cmd->split_cmd;
	if (ft_same_str(f[0], "cd", 2))
		return (ft_cd(f, shell));
	else if (ft_same_str(f[0], "export", 6))
		return (ft_export(f, shell));
	else if (ft_same_str(f[0], "unset", 5))
		return (ft_unset(f));
	else if (ft_same_str(f[0], "env", 3))
		return (ft_env(shell->envp));
	else if (ft_same_str(f[0], "exit", 4))
		return (ft_exit(f, shell));
	shell->spec_built = FALSE;
	return (0);
}

int	executor(t_data *shell)
{
	int		status;
	int		ret;

	prepare_heredocs(shell);
	if (shell->nb_cmd > 1)
	{
		if (!init_pipes(shell))
			exit_free(shell, 127);
	}
	
	ret = special_built(shell->exec, shell);
	if (shell->spec_built)
		return (ret);
	fork_cmd(shell);
	close_wait(shell);
	return (shell->last_return_code);
}
