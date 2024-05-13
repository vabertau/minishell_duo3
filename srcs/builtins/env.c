/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:47:00 by hedi              #+#    #+#             */
/*   Updated: 2024/05/12 17:02:21 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

char	*ft_strndup_var(const char *s, int n)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (i <= n)
		ret = malloc(sizeof(char) * (i + 1));
	else
		ret = malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (0);
	while (j < i && j < n)
	{
		ret[j] = s[j];
		j++;
	}
	if (ret[j - 1] == '=')
		--j;
	ret[j] = '\0';
	return (ret);
}

char	**malloc_var(int i, char *s, int j, int n)
{
	char **ret;

	ret = malloc(sizeof(char *) * (n + 1));
	if (!ret)
		return (NULL);
	ret[0] = ft_strndup_var(s, (j));
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	if(n == 2)
	{
		ret[1] = ft_strdup(s + i);
		if (!ret[1])
		{
			free(ret[0]);
			free(ret);
			return (NULL);
		}
		ret[2] = NULL;
	}
	else
		ret[1] = NULL;
	return (ret);
}
char **split_var(char *s, t_data *shell)
{
	int	i;
	int	n;
	int	j;
	char **ret;

	i = 0;
	while (s && s[i] && s[i] != '=' && s[i] != '+')
		i++;
	n = 1;
	j = i;
	if (s[i])
		n = 2;
	if (s[i] == '+' && s[i+1] == '=')
		i += 2;
	else if (s[i] == '=')
		i++;
	ret = malloc_var(i, s, j, n);
	return (ret);
}
int	find_index_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=' )
		i++;
	return (i);
}

int	have_equal(char *env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (env[i] == '=')
			return (i);
	return (0);
}

int	var_in_env(char *s, t_data *shell)
{
	int		ret;
	int		j;
	t_env 	*tmp;
	char	**var;

	
	var = split_var(s, shell);
	
	tmp = shell->env;
	if (!var)
	{
		perror("malloc");
		exit_free(shell, EXIT_FAILURE);
	}
	
	ret = -1;
	j = -1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, var[0]))
			ret = tmp->index;
		
		tmp = tmp->next;
	}
	//printf("\ntest\n");
	if (var[1])
		free(var[1]);
	free(var[0]);
	free(var);
	//printf("\ntest\n");
	return (ret);
}
int check_plus(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=' && s[i] != '+')
		i++;
	if (s[i] == '+')
		return(1);
	else
		return (0);
	return (-1);
}

void	ft_update_env(char *str, t_data *shell, int pos)
{
	char **s;
	int	index;
	t_env	*tmp;

	s = split_var(str, shell);
	tmp = shell->env;
	if (!s)
		return ;
	if (check_plus(str))
	{
		while (tmp && tmp->index < pos)
			tmp = tmp->next;
		tmp->val = join_free1(tmp->val, s[0]);
		if (!tmp->val)
			perror("malloc");
		free(tmp->var);
		tmp->var = join_free1(ft_strjoin(tmp->var_name, "="),tmp->val);
		if (!tmp->var)
			perror("malloc");
	}
	else
	{
		while (tmp && tmp->index < pos)
			tmp = tmp->next;
		if (s[1] || have_equal(tmp->var))
		{
			free(tmp->val);
			tmp->val = ft_strdup(s[1]);
			if (!tmp->val)
				perror("malloc");
		}
		free(tmp->var);
		tmp->var = join_free1(ft_strjoin(tmp->var_name, "="),tmp->val);
		if (!tmp->var)
			perror("malloc");

	}
	
	
}

void	ft_add_env(char *s, t_data *shell)
{
	char **str = split_var(s, shell);
	if (!str) return;

	t_env *new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc");
		return; // Gérer l'échec de l'allocation plus proprement si nécessaire
	}

	new_node->var = join_free1(ft_strjoin(str[0], "="), str[1]);
	new_node->var_name = ft_strdup(str[0]);
	new_node->val = str[1] ? ft_strdup(str[1]) : NULL;
	new_node->next = NULL;

	if (shell->env == NULL)
	{
		shell->env = new_node; // Cas où la liste était vide
		new_node->index = 0;
	}
	else
	{
		t_env *e = shell->env;
		while (e->next != NULL)
			e = e->next; // Parcourir jusqu'au dernier élément
		e->next = new_node;
		new_node->index = e->index + 1;
	}

	if (!new_node->var || !new_node->val || !new_node->var_name)
	{
		perror("malloc");
		// Doit gérer la libération de la mémoire allouée précédemment
	}
}


int	ft_putenv(char *s, t_data *shell)
{
	int pos;
	
	pos = var_in_env(s, shell);
	printf("\n%d\n", pos);
	if (pos > -1)
		ft_update_env(s, shell, pos);
	else
		ft_add_env(s, shell);
	return 1;
}

void ft_printf_var_env(char *var)
{
	write(STDOUT_FILENO,"declare -x ", 11);
	write(STDOUT_FILENO, var, ft_strlen(var));
	write(STDOUT_FILENO, "\n", 1);
}

int check_cmd(char *s)
{
	int i;

	i = 0;
	if (!s[0] || (s[0] != '_' && !ft_isalpha(s[0])))
		return (0);
	while(++i && s && s[i] && s[i] != '=' && s[i] != '+')
		if ((s[i] != '_' && !ft_isalnum(s[i])))
			return (0);
	if (s[i] == '+' && s[i + 1] != '=')
		return (0);
	return (1);
}

int	ft_export(char **split_cmd, t_data *shell)
{
	int	i;
	char *tmp;
	t_env	*e;
	e = shell->env;
	
	if (split_cmd[1] == NULL)
	{
		i = -1;
		while (e)
		{
			ft_printf_var_env(e->var);
			e = e->next;
		}
	}
	i = 0;
	while (split_cmd[++i] != NULL)
	{
		if (!check_cmd(split_cmd[i]))
		{
			tmp = ft_strjoin("bash: export: `", split_cmd[i]);
			ft_putstr_fd_free(join_free1(tmp, "': not a valid identifier\n"), 2);
		}
		else if (ft_putenv(split_cmd[i], shell) != 1) // Add to the environment
		{
			perror("export");
			exit_free(shell, EXIT_FAILURE);
		}
	}
	return (0);
}

int	ft_unset(char **split_cmd)
{
	int i = 1;
	while (split_cmd[i] != NULL)
	{
		unsetenv(split_cmd[i]);
		i++;
	}
	return (0);
}

int	ft_env(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}