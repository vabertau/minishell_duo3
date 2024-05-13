/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_to_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:00:16 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/09 17:02:00 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks for an index of a word if it is to expand
*/

bool	is_to_expand(char *word)
{
	int	i;

	i = 0;
	if (word[i] == '$' && word[i + 1] && (ft_isalnum(word[i + 1])
			|| word[i + 1] == '_' || word[i + 1] == '?'))
		return (1);
	return (0);
}
