/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_schar_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:06:04 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/09 16:54:47 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
That function is called when a pipe is found.
It checks that the next found character is not a pipe,
skipping spaces.
*/
static int	check_if_next_is_pipe(char *cmdline)
{
	int	i;

	i = 1;
	while (cmdline[i])
	{
		if (cmdline[i] != ' ' && cmdline[i] != '|')
			return (0);
		else if (cmdline[i] == ' ')
			i++;
		else if (cmdline[i] == '|')
			return (1);
	}
	return (0);
}

/*
Returns 1 if error >| or >     | type is found
*/
static int	check_for_append_pipe(t_data *data)
{
	int		i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'')
			i += skip_sq(&(cmdline[i]));
		if (cmdline[i] == '\"')
			i += skip_dq(&(cmdline[i]));
		if (cmdline[i] == '>' || cmdline[i] == '<')
		{
			i++;
			while (cmdline[i] == '>' || cmdline[i] == '<' || cmdline[i] == ' ')
				i++;
			if (cmdline[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_forbidden(char c)
{
	if (c == '\\' || c == ';' || c == '\0' || c == '&' || c == '*' || c == '('
		|| c == ')')
		return (1);
	return (0);
}

static int	check_schar_inception(t_data *data, char *cmdline, int i)
{
	if (cmdline[i] == '|')
		if (check_if_next_is_pipe(&(cmdline[i])) == 1)
			return ((void)parsing_error(data), 1);
	if (cmdline[i + 1] && ((cmdline[i] == '>' && cmdline[i + 1] == '<')
			|| (cmdline[i] == '<' && cmdline[i + 1] == '>')))
		return ((void)parsing_error(data), 1);
	if ((cmdline[i + 1] && cmdline[i + 2]) && ((cmdline[i] == '<'
				&& cmdline[i + 1] == '<' && (cmdline[i + 2] == '<'
					|| cmdline[i + 2] == '>')) || (cmdline[i] == '>'
				&& cmdline[i + 1] == '>' && (cmdline[i + 2] == '>'
					|| cmdline[i + 2] == '<'))))
		return ((void)parsing_error(data), 1);
	if (check_forbidden(cmdline[i]) == 1)
		return ((void)parsing_error(data), 1);
	return (0);
}

/*
Checks for parsing errors in cmdline, skipping charachters between quotes
*/
void	check_schar_error(t_data *data)
{
	int		i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'')
			i += skip_sq(&(cmdline[i]));
		if (cmdline[i] == '\"')
			i += skip_dq(&(cmdline[i]));
		if (check_schar_inception(data, cmdline, i))
			return ;
		i++;
	}
	if (check_for_append_space_append(data) == 1)
		return ((void)parsing_error(data));
	if (check_for_append_pipe(data) == 1)
		return ((void)parsing_error(data));
}
