/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfill_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:47:39 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 14:03:05 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_redir_inc(t_data *data, t_exec **tmp_exec, t_token **tmp_redir,
		int j)
{
	if (j == 0)
	{
		(*tmp_exec)->redir = malloc(sizeof(t_token));
		if (!(*tmp_exec)->redir)
			exit_free(data, -1);
		*tmp_redir = (*tmp_exec)->redir;
	}
	else
	{
		(*tmp_redir)->next = malloc(sizeof(t_token));
		if (!(*tmp_redir))
			exit_free(data, -1);
		*tmp_redir = (*tmp_redir)->next;
	}
}

/*
Malloc data->exec->nb_redirections nodes in t_exec. Those will be filled with
word = infile and type = >
*/
void	malloc_redir(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	t_token	*tmp_redir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp_exec = data->exec;
	tmp_token = data->token;
	while (i < data->nb_cmd)
	{
		j = 0;
		while (j < tmp_exec->nb_redir)
		{
			malloc_redir_inc(data, &tmp_exec, &tmp_redir, j);
			j++;
		}
		if (j > 0)
			tmp_redir->next = NULL;
		tmp_exec = tmp_exec->next;
		i++;
	}
}

void	fill_redir_inc(t_token *tmp_token, t_token **tmp_redir,
		t_token *previous_token, int i_j[2])
{
	if (tmp_token->type == WORD && (previous_token != NULL)
		&& (previous_token->type == RIGHT1 || previous_token->type == RIGHT2
			|| previous_token->type == LEFT1 || previous_token->type == LEFT2))
	{
		(*tmp_redir)->word = tmp_token->word;
		(*tmp_redir)->type = previous_token->type;
		*tmp_redir = (*tmp_redir)->next;
		i_j[1]++;
	}
}

static t_token	*init_var(t_data *data, int (*i_j)[2], t_exec **tmp_exec,
		t_token **tmp_token)
{
	(*i_j)[0] = 0;
	(*i_j)[1] = 0;
	*tmp_exec = data->exec;
	*tmp_token = data->token;
	return ((*tmp_exec)->redir);
}

/*
Iterates on all the tokens
For each cmd, while j < tmp_exec->nb_redir,
int *i_j because to many variable declarations in function
*/
void	fill_redir(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	t_token	*previous_token;
	t_token	*tmp_redir;
	int		i_j[2];

	nb_redir(data);
	malloc_redir(data);
	tmp_redir = init_var(data, &i_j, &tmp_exec, &tmp_token);
	previous_token = NULL;
	while (i_j[0] < data->nb_tokens)
	{
		fill_redir_inc(tmp_token, &tmp_redir, previous_token, i_j);
		if (i_j[1] == tmp_exec->nb_redir)
		{
			if (tmp_exec->next == NULL)
				return ;
			tmp_exec = tmp_exec->next;
			tmp_redir = tmp_exec->redir;
			i_j[1] = 0;
		}
		i_j[0]++;
		previous_token = tmp_token;
		tmp_token = tmp_token->next;
	}
}
