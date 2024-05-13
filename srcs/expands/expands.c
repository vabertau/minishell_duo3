/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:46:03 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 11:43:34 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	varlen(char *word)
{
	int	ret;
	int	i;

	ret = 0;
	i = 1;
	if (word[1] == '?')
		return (1);
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_' || word[i] == '?'))
	{
		ret++;
		i++;
	}
	return (ret);
}

char	*fetch_var_content(t_data *data, char *var, char **env)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			ret = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			if (!ret)
				return (free(var), exit_free(data, -1), NULL);
			return (ret);
		}
		i++;
	}
	ret = ft_strdup("");
	if (!ret)
		return (free(var), exit_free(data, -1), NULL);
	data->void_expand = 1;
	return (ret);
}
/*
void	fill_ret(t_data *data, char **word, char *var_cont, char *var_name)
{
	ret = malloc(sizeof(char) * (ft_strlen(*word) + ft_strlen(var_cont) + 1));
	if (ret == NULL)
		return ((void)free(var_name), (void)free(var_cont), exit_free(data,
				-1));
	ft_strlcpy(ret, *word, i + 1);
	ft_strlcat(ret, var_cont, ft_strlen(ret) + ft_strlen(var_cont) + 1);
	if (ret == NULL)
		return ((void)free(var_name), (void)free(var_cont), exit_free(data,
				-1));
	ft_strlcat(ret, &((*word)[i + len_var + 1]), ft_strlen(ret)
		+ ft_strlen(&((*word)[i + len_var + 1])) + 1);
	if (ret == NULL)
		return ((void)free(var_name), (void)free(var_cont), exit_free(data,
				-1));
	free(*word);
}
*/
/*
static char	*init_replace_var(t_data *data, char **word, int i, int len_var)
{
	char	*var_name;

	var_name = ft_substr(*word, i + 1, len_var);
	data->void_expand = 0;
	if (!var_name)
		exit_free(data, -1);
	return (var_name);
}

static char	*ft_itoa_protect(t_data *data, char *var_name)
{
	char	*var_c;

	var_c = ft_itoa(data->last_return_code);
	if (var_c == NULL)
		return (free(var_name), exit_free(data, -1), NULL);
	return (var_c);
}
*/
/* var_c = var_content */
/*
void	replace_var(t_data *data, char **word, int i, int len_var)
{
	char	*var_name;
	char	*var_c;
	char	*ret;

	var_name = init_replace_var(data, word, i, len_var);
	if ((len_var == 1) && (*word)[i + 1] == '?')
		var_c = ft_itoa_protect(data, var_name);
	else
		var_c = fetch_var_content(data, var_name, data->env);
	ret = malloc(sizeof(char) * (ft_strlen(*word) + ft_strlen(var_c) + 1));
	if (ret == NULL)
		return ((void)free(var_name), (void)free(var_c), exit_free(data, -1));
	ft_strlcpy(ret, *word, i + 1);
	ft_strlcat(ret, var_c, ft_strlen(ret) + ft_strlen(var_c) + 1);
	if (ret == NULL)
		return ((void)free(var_name), (void)free(var_c), exit_free(data, -1));
	ft_strlcat(ret, &((*word)[i + len_var + 1]), ft_strlen(ret)
		+ ft_strlen(&((*word)[i + len_var + 1])) + 1);
	if (ret == NULL)
		return ((void)free(var_name), (void)free(var_c), exit_free(data, -1));
	free(*word);
	*word = ret;
	return ((void)(free(var_name)), (void)(free(var_c)));
}
*/
/*
Iterates through all the characters of a word
If character is a $ and its an expand

gets in len_var the len of the variable: ft_strlen but alnum, _ or ?
*/

void	launch_expand(t_data *data, t_token *token)
{
	int		i;
	char	*word;
	int		len_var;

	word = token->word;
	i = 0;
	while (word[i])
	{
		if (is_to_expand(&(word[i])))
		{
			len_var = varlen(&(word[i]));
			replace_var(data, &word, i, len_var);
			i += len_var;
		}
		i++;
	}
	token->word = word;
}

/*
Expands if data->is_bq != 1 (not between sq) and a $ is found
*/

int	expands(t_data *data)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = data->token;
	while (i < data->nb_tokens)
	{
		if (!(data->is_bq[i] == 1) && ft_strchr(tmp->word, '$'))
			launch_expand(data, tmp);
		i++;
		tmp = tmp->next;
	}
	return (0);
}
