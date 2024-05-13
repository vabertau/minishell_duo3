/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfill_full_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:50:24 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 14:21:26 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Fills full_command in exec struct. Full command will be used in exec.
ft_strdup for first word,
	then using ft_strjoin to add space and then to add next word
*/

static char	*ft_strfreejoin(char *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (free(s1), NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	free(s1);
	return (ret);
}

static void	init_full_cmd(t_data *data)
{
	t_exec	*tmp_exec;
	int		i;

	i = 0;
	tmp_exec = data->exec;
	while (i < data->nb_cmd)
	{
		tmp_exec->full_cmd = NULL;
		tmp_exec = tmp_exec->next;
		i++;
	}
}

void	fill_full_cmd_inc(t_data *data, t_exec **tmp_exec, t_token **tmp_token)
{
	if ((*tmp_exec)->full_cmd == NULL)
	{
		(*tmp_exec)->full_cmd = ft_strdup((*tmp_token)->word);
		if ((*tmp_exec)->full_cmd == NULL)
			exit_free(data, -1);
	}
	else
	{
		(*tmp_exec)->full_cmd = ft_strfreejoin((*tmp_exec)->full_cmd, " ");
		if ((*tmp_exec)->full_cmd == NULL)
			exit_free(data, -1);
		(*tmp_exec)->full_cmd = ft_strfreejoin((*tmp_exec)->full_cmd,
				(*tmp_token)->word);
		if ((*tmp_exec)->full_cmd == NULL)
			exit_free(data, -1);
	}
	*tmp_token = (*tmp_token)->next;
}

void	fill_full_cmd(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_exec = data->exec;
	tmp_token = data->token;
	init_full_cmd(data);
	while (i < data->nb_cmd)
	{
		while (tmp_token && tmp_token->type != PIPE)
			fill_full_cmd_inc(data, &tmp_exec, &tmp_token);
		if (tmp_token)
			tmp_token = tmp_token->next;
		tmp_exec = tmp_exec->next;
		i++;
	}
}
