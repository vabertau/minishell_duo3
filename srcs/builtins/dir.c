/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:46:16 by hedi              #+#    #+#             */
/*   Updated: 2024/05/13 18:06:09 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **split_cmd, t_data *shell)
{
	if (split_cmd[2])
		ft_putstr_fd("cd: too many arguments", 2);
	if (split_cmd[1] == NULL || chdir(split_cmd[1]) != 0)
	{
		perror("cd");
		exit_free(shell, EXIT_FAILURE);
	}
	return (0);
}

int	ft_pwd(t_data *shell)
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	perror("pwd");
	exit_free(shell, EXIT_FAILURE);
	return (1);
}