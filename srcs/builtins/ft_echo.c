/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:27:39 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/13 18:30:35 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **split_cmd)
{
	int		i;
	bool	nl_to_put;

	i = 1;
	nl_to_put = 1;
	if (split_cmd[1] && !ft_strncmp(split_cmd[1], "-n", 3))
	{
		nl_to_put = 0;
		i++;
	}
	while (split_cmd[i])
	{
		ft_putstr_fd(split_cmd[i], STDOUT_FILENO);
		if (split_cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl_to_put)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	str_is_num(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s && s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	}
	return (1);
}

int	ft_exit(char **split_cmd, t_data *data)
{
	int exit_status;

	exit_status = 0;
	if (split_cmd[2])
	{
		ft_putstr_fd("exit: too many arguments", 2);
		exit_status = 1;
	}
	else
	{
		if (split_cmd[1] != NULL && str_is_num(split_cmd[1]))
			exit_status = ft_atoi(split_cmd[1]);
		if (split_cmd[1] != NULL  && !str_is_num(split_cmd[1]))
		{
			ft_putstr_fd("exit: numeric argument required", 2);
			exit_status = 2;
		}
	}

	exit_free(data, exit_status);
	return (exit_status); // This will end the program
}


/*
int	main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	ft_echo(&(argv[1]));
	return (0);
}
*/
