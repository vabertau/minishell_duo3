/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:42:54 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/12 18:13:25 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/* var_c = var_content */
void	replace_var(t_data *data, char **word, int i, int len_var)
{
	char	*var_name;
	char	*var_c;
	char	*ret;

	var_name = init_replace_var(data, word, i, len_var);
	if ((len_var == 1) && (*word)[i + 1] == '?')
		var_c = ft_itoa_protect(data, var_name);
	else
		var_c = fetch_var_content(data, var_name, data->envp);
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
