/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_bet_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:48:08 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 12:53:49 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Searches for a missing space before a special character,
	and adds it if it is missing
 */
static int	add_space_bf(int i, char *ret, char *tmp)
{
	if (i > 0 && ret[i - 1] != '<' && ret[i - 1] != '>' && ret[i - 1] != '|'
		&& ret[i - 1] != ' ')
	{
		ft_strlcpy(&(ret[i + 1]), &(tmp[i]), ft_strlen(&(ret[i])) + 1);
		ret[i] = ' ';
		return (1);
	}
	return (0);
}

/* Searches for a missing space after a special character,
	and adds it if it is missing
 */
static void	add_space_af(int i, int sp_bf, char *ret, char *tmp)
{
	if (tmp[i + 1] != '<' && tmp[i + 1] != '>' && tmp[i + 1] != '|' && tmp[i
			+ 1] != ' ')
	{
		if (sp_bf == 1)
		{
			ft_strlcpy(&(ret[i + 3]), &(tmp[i + 1]), ft_strlen(&tmp[i + 1])
				+ 1);
			ret[i + 2] = ' ';
		}
		else
		{
			ft_strlcpy(&(ret[i + 2]), &(tmp[i + 1]), ft_strlen(&(tmp[i + 1]))
				+ 1);
			ret[i + 1] = ' ';
		}
	}
}

/* Calls functions to add space before and after special
characters if a space is missing.
stores a boolean sp_bf for index matters in add_space_af */
static void	add_space_bf_af(int i, char *ret, char *tmp)
{
	bool	sp_bf;

	sp_bf = add_space_bf(i, ret, tmp);
	add_space_af(i, sp_bf, ret, tmp);
}

/*skips characters between quotes,
	and calls function to add missing spaces between and
after separators
*/
char	*add_space(char *cmdline, t_data *data)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (fixed_cmdline_len(cmdline) + 1));
	if (ret == NULL)
		exit_free(data, -1);
	ft_strlcpy(ret, cmdline, ft_strlen(cmdline) + 1);
	while (ret[i])
	{
		i += skip_sq(&(ret[i]));
		i += skip_dq(&(ret[i]));
		if (ret[i] == '<' || ret[i] == '>' || ret[i] == '|')
		{
			tmp = ft_strdup(ret);
			if (!tmp)
				return (free(ret), exit_free(data, -1), NULL);
			add_space_bf_af(i, ret, tmp);
			free(tmp);
		}
		i++;
	}
	return (free(cmdline), ret);
}

/*add_spaces function launcher*/
int	spaces_bet_tokens(t_data *data)
{
	data->cmdline = add_space(data->cmdline, data);
	return (0);
}
