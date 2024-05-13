/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unclosedq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:39:43 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/09 16:55:25 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Checks for unclosed quotes in the beginning and returns
parsing error if there are any.
Better to check in the beginning,
	allows not to handle unclosed quotes in tokens*/
int	check_unclosedq(t_data *data)
{
	int		i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'' && ft_strchr(&(cmdline[i + 1]), '\''))
			i += skip_sq(&(cmdline[i])) + 1;
		else if (cmdline[i] == '\'')
			return (parsing_error(data), -1);
		if (cmdline[i] == '\"' && ft_strchr(&(cmdline[i + 1]), '\"'))
			i += skip_dq(&(cmdline[i])) + 1;
		else if (cmdline[i] == '\"')
			return (parsing_error(data), -1);
		else
			i++;
	}
	return (0);
}
