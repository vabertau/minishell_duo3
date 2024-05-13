/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotesplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:28:26 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 19:18:06 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
static int	nb_chains(char const *s, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			ret++;
			i++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (ret);
}
*/
static void	init_var(int *k, int j, t_data *data)
{
	*k = 0;
	data->is_bq[j] = 0;
}

static void	copy_char(int *k, int *i, char const *s, char *tmp)
{
	tmp[*k] = s[*i];
	(*i)++;
	(*k)++;
}

/*
Starts with too big malloc (ft_strlen(cmdline) + 1 the biggest possible).
Copies 1 token, stopping at first ' ' that is not between quotes.
copy_bet_quotes functions copies character between quotes without
the quotes SQ TO ADD ??
In the end resizing the malloc with ft_strdup and freeing tmp which is too big,
	too avoid unnecessary space use.

data->is_bq is filled to track if it is between closed quotes,
	as quotes are suppressed we can't track it after
it is a temporary int *, used later to fill token types = DQUOTE

Added copy_bet_q in if statement for line gain
*/
static char	*ft_substr_quotes(t_data *data, char const *s, int *i, int j)
{
	char	*ret;
	char	*tmp;
	int		k;

	tmp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tmp)
		return (NULL);
	init_var(&k, j, data);
	while (s[*i] && s[*i] != ' ')
	{
		if ((s[*i] == '\'') && ft_strchr(&(s[(*i) + 1]), '\'')
			&& !(copy_bet_sq(i, &k, s, tmp)))
			data->is_bq[j] = 1;
		else if ((s[*i] == '\"') && ft_strchr(&(s[(*i) + 1]), '\"'))
		{
			copy_bet_dq(i, &k, s, tmp);
			data->is_bq[j] = 2;
		}
		else
			copy_char(&k, i, s, tmp);
	}
	tmp[k] = '\0';
	ret = ft_strdup(tmp);
	return (free(tmp), ret);
}

static void	init_ftqs(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

/*
static int	first_nonc(char const *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}
*/
/* Similar to ft_split,
	but it will not split with c character when inside quotes.

As ft_substr_quotes suppresses the quotes, data->is_bq[i] stock the info 1 if
the token was between quotes, 0 if not. Later in fill-type, that double tab
will be used to fill token type DQUOTE if data->is_bq[i] == 1
*/
char	**ft_quotesplit(t_data *data, const char *s)
{
	char	**ret;
	int		i;
	int		j;

	init_ftqs(&i, &j);
	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (nb_chains(s, ' ') + 1));
	if (!ret)
		exit_free(data, -1);
	data->is_bq = malloc(sizeof(int) * (data->nb_tokens + 1));
	if (!data->is_bq)
		return (free(ret), exit_free(data, -1), NULL);
	while (s[i])
	{
		i = first_nonc(s, ' ', i);
		if (!(s[i]))
			break ;
		ret[j] = ft_substr_quotes(data, s, &i, j);
		if (!ret[j])
			return (free(ret), exit_free(data, -1), NULL);
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

/*
#include <stdio.h>
*/
/* ================== test nb_chains ================= */
/*
int	main(void)
{
	char	**result;
	int		i;

	printf("result = %i", nb_chains("test", 'a'));
}*/
/* =============== test ft_split =================== */
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void	test_ft_split(char const *s, char c)
{
	result = ft_split(s, c);
	if (result == NULL)
	{
		printf("ft_split returned NULL\n");
		return ;
	}
	i = 0;
	while (result[i] != NULL)
	{
		printf("result[%d] = \"%s\"\n", i, result[i]);
		free(result[i]);
		i++;
	}
	free(result[i]);
	free(result);
}

int	main(void)
{
	test_ft_split("Hello,World!", ',');
	test_ft_split("split  ||this|for|me|||||!|", '|');
	test_ft_split("Hello,World!,How,Are,You?", '!');
	test_ft_split("Hello,World!,How,Are,You?", ' ');
	test_ft_split("Hello,World!,How,Are,You?", '\0');
	test_ft_split("", ',');
	test_ft_split(NULL, ',');
	return (0);
}*/
