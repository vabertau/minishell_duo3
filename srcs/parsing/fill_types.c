/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:22 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 17:03:37 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (!us1 || !us2)
		return (0);
	while (us1[i] && us2[i] && (us1[i] == us2[i]))
		i++;
	return (us1[i] - us2[i]);
}

void	fill_types(t_data *data)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = data->token;
	while (i < data->nb_tokens)
	{
		if (!ft_strcmp(tmp->word, "|"))
			tmp->type = PIPE;
		else if (!ft_strcmp(tmp->word, "<"))
			tmp->type = LEFT1;
		else if (!ft_strcmp(tmp->word, ">"))
			tmp->type = RIGHT1;
		else if (!ft_strcmp(tmp->word, ">>"))
			tmp->type = RIGHT2;
		else if (!ft_strcmp(tmp->word, "<<"))
			tmp->type = LEFT2;
		else
			tmp->type = WORD;
		i++;
		tmp = tmp->next;
	}
}
