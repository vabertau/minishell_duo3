/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:03:31 by hedi              #+#    #+#             */
/*   Updated: 2024/05/13 20:01:41 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input_redirection(t_token *redir, t_data *shell)
{
	redir->fd = safe_open(redir->word, O_RDONLY, 0, shell);
	if (redir->fd == -1)
	{
		perror("open");
		exit_free(shell, EXIT_FAILURE);
	}
	safe_dup2(redir->fd, STDIN_FILENO, shell);
	safe_close(redir->fd, shell);
}

void	handle_output_redirection(t_token *redir, t_data *shell)
{
	int	fd;

	if (redir->type == RIGHT1)
		fd = safe_open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644, shell);
	if (redir->type == RIGHT2)
		fd = safe_open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644, shell);
	redir->fd = fd;
	if (redir->fd == -1)
	{
		perror("open");
		exit_free(shell, EXIT_FAILURE);
	}
	if (redir->next == NULL || redir->next->type != RIGHT1
		|| redir->next->type != RIGHT2)
		safe_dup2(redir->fd, STDOUT_FILENO, shell);
	safe_close(redir->fd, shell);
}

void	handle_redirections(t_exec *cmd, t_data *shell)
{
	t_token	*redir;

	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == LEFT1 || redir->type == LEFT2)
			handle_input_redirection(redir, shell);
		else if (redir->type == RIGHT1 || redir->type == RIGHT2)
			handle_output_redirection(redir, shell);
		redir = redir->next;
	}
}

void	prepare_heredocs(t_data *shell)
{
	int		cpt;
	t_exec	*current_cmd;
	t_token	*redir;

	cpt = 0;
	current_cmd = shell->exec;
	while (current_cmd)
	{
		redir = current_cmd->redir;
		while (redir)
		{
			if (redir->type == LEFT2)
				fill_redir_heredoc(shell, &cpt, redir);
			redir = redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

void	fill_redir_heredoc(t_data *shell, int *cpt, t_token *redir)
{
	int		fd;
	char	*line;
	char	*full_path;

	heredoc_signals();
	full_path = join_free2("/tmp/heredoc_", ft_itoa((*cpt)++));
	fd = safe_open(full_path, O_RDWR | O_CREAT | O_TRUNC, 0600, shell);
	line = readline("> ");
	while ((line) != NULL)
	{
		if (ft_strcmp(line, redir->word) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	safe_close(fd, shell);
	redir->word = ft_strdup(full_path);
	free(full_path);
}
