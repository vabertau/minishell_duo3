/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:47:05 by hedi              #+#    #+#             */
/*   Updated: 2024/05/08 21:02:26 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	safe_open(const char *pathname, int flags, mode_t mode, t_data *shell)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
	{
		perror("open");
		exit_free(shell, EXIT_FAILURE);
	}
	return (fd);
}

void	safe_close(int fd, t_data *shell)
{
	if (close(fd) == -1)
	{
		perror("close");
		exit_free(shell, EXIT_FAILURE);
	}
}

void	safe_dup2(int oldfd, int newfd, t_data *shell)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit_free(shell, EXIT_FAILURE);
	}
}