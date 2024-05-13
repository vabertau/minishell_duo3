/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfill_split_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:04:19 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 13:09:32 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_var(int *i, int *j, t_token **previous_token)
{
	*i = 0;
	*j = 0;
	*previous_token = NULL;
}

static void	count_words(t_token *tmp_token, t_token *previous_token, int *j)
{
	if (tmp_token->type == WORD && !((previous_token != NULL)
			&& (previous_token->type == RIGHT1 || previous_token->type == RIGHT2
				|| previous_token->type == LEFT1
				|| previous_token->type == LEFT2)))
		(*j)++;
}

/*
Goes through all the tokens,
	if token is part of a command (token is a word and previous token is
not a redir), increments j which is the number of char * to malloc.

When finding a pipe, end of the command, malloc split_cmd sizeof(char *) * (j
	+ 1)
And			tmp_exec = tmp_exec->next to fill next split_cmd
*/
static void	malloc_split_cmd(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	t_token	*previous_token;
	int		i;
	int		j;

	tmp_exec = data->exec;
	tmp_token = data->token;
	init_var(&i, &j, &previous_token);
	while (i < data->nb_tokens)
	{
		count_words(tmp_token, previous_token, &j);
		if (tmp_token->type == PIPE || (i + 1) == data->nb_tokens)
		{
			tmp_exec->split_cmd = malloc(sizeof(char *) * (j + 1));
			if (!tmp_exec->split_cmd)
				exit_free(data, -1);
			j = 0;
			tmp_exec = tmp_exec->next;
		}
		previous_token = tmp_token;
		tmp_token = tmp_token->next;
		i++;
	}
}

static void	fill_words(t_token *tmp_token, t_token *previous_token, int *j,
		t_exec **tmp_exec)
{
	if (tmp_token->type == WORD && !((previous_token != NULL)
			&& (previous_token->type == RIGHT1 || previous_token->type == RIGHT2
				|| previous_token->type == LEFT1
				|| previous_token->type == LEFT2)))
	{
		(*tmp_exec)->split_cmd[*j] = tmp_token->word;
		(*j)++;
	}
}

/*
Calls malloc_split_cmd to malloc each tmp_exec->split_cmd with sizeof(char *)
* the number of words in each command + 1.

Then fills in each node of tmp_exec split_cmd with each word of the command.
*/
void	fill_split_cmd(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	t_token	*previous_token;
	int		i;
	int		j;

	malloc_split_cmd(data);
	tmp_exec = data->exec;
	tmp_token = data->token;
	init_var(&i, &j, &previous_token);
	while (i < data->nb_tokens)
	{
		fill_words(tmp_token, previous_token, &j, &tmp_exec);
		if (tmp_token->type == PIPE || (i + 1) == data->nb_tokens)
		{
			tmp_exec->split_cmd[j] = NULL;
			j = 0;
			tmp_exec = tmp_exec->next;
		}
		previous_token = tmp_token;
		tmp_token = tmp_token->next;
		i++;
	}
}
