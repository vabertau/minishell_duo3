/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fasa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:52:43 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/09 16:53:26 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
checks for < < or < >
*/
static int	check_left1(char *cmdline, int *i, bool *space_found)
{
	if (cmdline[*i] == '<')
	{
		(*i)++;
		while (cmdline[*i] == ' ')
		{
			(*i)++;
			*space_found = 1;
		}
		if (cmdline[*i] == '<' || cmdline[*i] == '>')
		{
			if (*space_found == 1)
				return (1);
		}
		*space_found = 0;
	}
	return (0);
}

/*
checks for > < or > >
*/
static int	check_right1(char *cmdline, int *i, bool *space_found)
{
	if (cmdline[*i] == '>')
	{
		(*i)++;
		while (cmdline[*i] == ' ')
		{
			(*i)++;
			*space_found = 1;
		}
		if (cmdline[*i] == '<' || cmdline[*i] == '>')
		{
			if (*space_found == 1)
				return (1);
		}
		*space_found = 0;
	}
	return (0);
}

/*
Checks for >    > return 1 if that error is found
*/
int	check_for_append_space_append(t_data *data)
{
	int		i;
	char	*cmdline;
	bool	space_found;

	i = 0;
	space_found = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'')
			i += skip_sq(&(cmdline[i]));
		if (cmdline[i] == '\"')
			i += skip_dq(&(cmdline[i]));
		if (check_left1(cmdline, &i, &space_found))
			return (1);
		if (check_right1(cmdline, &i, &space_found))
			return (1);
		i++;
	}
	return (0);
}
