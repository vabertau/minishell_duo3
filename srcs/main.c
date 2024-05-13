/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:54:44 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/13 17:57:01 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	aff_val(t_data *data)
{
	t_exec	*cur_cmd;
	t_token	*cur_redir;
	int		j;
	int		i;

	cur_cmd = data->exec;
	j = 1;
	while (cur_cmd && j++)
	{
		i = -1;
		cur_redir = cur_cmd->redir;
		printf("full[%d] = %s\n\n\n", j, cur_cmd->full_cmd);
		while (cur_cmd->split_cmd[++i])
			printf("split[%d][%d] = %s\n\n\n", j, i, cur_cmd->split_cmd[i]);
		while (cur_redir)
		{
			printf("%s\n%u\n", cur_redir->word, cur_redir->type);
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
}

int	len_env(t_env *env)
{
	t_env	*tmp;
	int i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	set_char_env(t_data *shell)
{
	t_env	*tmp;
	int		len;
	int		i;

	// if(shell->char_env)
	// 	free(shell->char_env);
	i = -1;
	tmp = shell->env;
	len = len_env(tmp);
	shell->char_env = malloc(sizeof(char *) * (len + 1));
	if (!shell->char_env)
		perror("malloc");
	while (++i < len && tmp)
	{
		shell->char_env[i] = ft_strdup(tmp->var);
		if (!shell->char_env[i])
			perror("malloc");
		tmp = tmp->next;
	}
	shell->char_env[i] = NULL;
}

void	trim_env(t_data *shell)
{
	t_env	*tmp;
	int		i;

	tmp = shell->env;
	while (shell->env != NULL)
	{
		i = 0;
		while (shell->env->var[i] && shell->env->var[i] != '=')
			i++;
		shell->env->var_name = ft_strndup(shell->env->var, i);

		if (!shell->env->var_name)
			perror("malloc");
		if (!shell->env->var[i++])
			return ;
		shell->env->val = ft_strdup(shell->env->var + i);
		if (!shell->env->val)
			perror("malloc");
		shell->env = shell->env->next;
	}
	shell->env = tmp;
}


t_env	*copy_envp(char **envp, t_data *shell)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	i = 0;
	head = NULL;
	tmp = NULL;
	while (envp[i])
	{
		if (tmp == NULL)
		{
			tmp = malloc(sizeof(t_env));
			if (!tmp)
				return (NULL);
			if (head == NULL)
				head = tmp;
		}
		tmp->var = ft_strdup(envp[i]);
		tmp->index = i;
		tmp->next = NULL;
		if (!tmp->var)
			return (NULL);
		if (envp[i + 1] != NULL)
		{
			tmp->next = malloc(sizeof(t_env));
			if (!tmp->next)
				return (NULL);
			tmp = tmp->next;
		}
		i++;
	}
	shell->env = head;
	return (head);
}


int	minishell_loop(t_data *data)
{
	data->sh_exit_loop = 0;
	data->pipe_fds = NULL;
	get_input(data);
	lexer(data);
	if (data->sh_exit_loop)
		return (-1);
	expands(data);
	parser(data);
	if (data->sh_exit_loop)
		return (-1);
	// aff_val(data);
	data->last_return_code = executor(data);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_env *e;
	// volatile sig_atomic_t signal_count = 0;
	//setup_signal_handlers(handle_sigint_interactive, handle_sigquit);
	(void)argc;
	(void)argv;
	data.char_env = NULL;
	data.last_return_code = 0;

	data.envp = envp;
	data.char_env = NULL;


	while (1)
	{
		data.env = copy_envp(envp, &data);
		trim_env(&data);
		set_char_env(&data);
		main_signals();
		init_data(&data);
		minishell_loop(&data);
		// if (!data.sh_exit_loop)
		free_all(&data);
		// printf("\n%d\n", data.last_return_code);
	}
	return (0);
	// exit_free(&data, 0); //tmp
}


/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	get_input(&data);
}
*/

//============ TEST NB_TOKENS ==============
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	//get_input(&data);
	data.cmdline = ft_strdup("test\"hey test\"");
	spaces_bet_tokens(&data);
	nb_tokens(&data);
	printf("nb tokens = %i\n", data.nb_tokens);
}
*/

// ============ TEST SPACES_BET_TOKENS ============

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	//while (1)
	//{
		//get_input(&data);
		data.cmdline = ft_strdup(">>>>>");
		spaces_bet_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ============ TEST NB_TOKENS ===============
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	init_data(&data);
	while (1)
	{
		get_input(&data);
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
		printf("nb tokens = %i\n", data.nb_tokens);
	}
	exit_free(&data, 0); //tmp
}
*/

// ============ TEST FILL_TOKENS ================
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		malloc_tokens(&data);
		if (data.token == NULL)
			printf("token = NULL");
		fill_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
		printf("nb tokens = %i\n", data.nb_tokens);
		tmp = data;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("is_bq = %i\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ============ TEST FILL_TOKENS  LLDB ================
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("test \" hey test\" hey\"");
		spaces_bet_tokens(&data);
		nb_tokens(&data);
		malloc_tokens(&data);
		if (data.token == NULL)
			printf("token = NULL");
		fill_tokens(&data);
		printf("cmdline = %s\n", data.cmdline);
		printf("nb tokens = %i\n", data.nb_tokens);
		tmp = data;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("is_bq = %i\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}

*/

// ======== TEST FILL_TYPES =========

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;
// 	t_data	tmp;
// 	t_type	test_type;
// 	int		i;

// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	i = 0;
// 	//while (1)
// 	//{
// 		init_data(&data, envp);
// 		get_input(&data);
// 		spaces_bet_tokens(&data);
// 		nb_tokens(&data);
// 		malloc_tokens(&data);
// 		if (data.token == NULL)
// 			printf("token = NULL");
// 		fill_tokens(&data);
// 		fill_types(&data);
// 		printf("cmdline = %s\n\n", data.cmdline);
// 		printf("nb tokens = %i\n\n", data.nb_tokens);
// 		tmp = data;
// 		test_type = WORD;
// 		while (tmp.token != NULL)
// 		{
// 			printf("word = %s\n", tmp.token->word);
// 			printf("type = %u\n", tmp.token->type);
// 			printf("is_bq = %i\n\n", data.is_bq[i]);
// 			tmp.token = tmp.token->next;
// 			i++;
// 		}
// 	//	free_bf_newprompt(&data);
// 	//}
// 	exit_free(&data, 0); //tmp
// }

// ======== TEST LEXER LLDB =============
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("hey \" hey\"");
		lexer(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ====== TEST LEXER =========
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data, envp);
		get_input(&data);
		lexer(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ===== TEST NB_CMD =======
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ===== TEST MALLOC EXEC & FILL_FULL_CMD =====
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ========== TEST FILL FULL CMD  LLDB ===========
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data, envp);
		//get_input(&data);
		data.cmdline = ft_strdup("echo \"> >> < * ? [ ] | ; [ ] ||
				&& ( ) & # $  <<\"");
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ========== TEST FILL FULL CMD LLDB ===========
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ===== NB_REDIR LLDB ======
/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup(">infile test1 test2 test3 test4");
		lexer(&data);
		parser(&data);
		nb_redir(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/
// ==== NB_REDIR ====

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		get_input(&data);
		lexer(&data);
		parser(&data);
		nb_redir(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ===== FILL_REDIR LLDB =====

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data);
		//get_input(&data);
		data.cmdline = ft_strdup("< infile test1 test2");
		lexer(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			if (tmp_exec->redir)
				printf("redir infile/outfile= %s\n", tmp_exec->redir->word);
			tmp_exec = tmp_exec->next;
		}
	//	free_bf_newprompt(&data);
	//}
	exit_free(&data, 0); //tmp
}
*/

// ==== FILL_REDIR ====

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	while (1)
	{
		init_data(&data, envp);
		get_input(&data);
		lexer(&data);
		parser(&data);
		executor(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		while (tmp.token != NULL)
		{
			printf("word = %s\n", tmp.token->word);
			printf("type = %u\n", tmp.token->type);
			printf("is_bq = %i\n\n", data.is_bq[i]);
			tmp.token = tmp.token->next;
			i++;
		}
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			printf("nb redir = %i\n", tmp_exec->nb_redir);
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			if (tmp_exec->redir)
			{
				printf("redir infile/outfile= %s\n", tmp_exec->redir->word);
				printf("redir type= %i\n\n", tmp_exec->redir->type);
			}
			tmp_exec = tmp_exec->next;
		}
		free_bf_newprompt(&data);
	}
	exit_free(&data, 0); //tmp
}
*/

// ==== EXPANDS LLDB ====

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_data	tmp;
	t_exec	*tmp_exec;
	t_type	test_type;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data, envp);
		//get_input(&data);
		data.cmdline = ft_strdup("echo \"$SHELL et autre chose\"");
		lexer(&data);
		expands(&data);
		parser(&data);
		printf("cmdline = %s\n\n", data.cmdline);
		printf("nb tokens = %i\n\n", data.nb_tokens);
		printf("nb_cmd = %i\n\n", data.nb_cmd);
		tmp = data;
		test_type = WORD;
		i = 0;
		tmp_exec = data.exec;
		while (i < data.nb_cmd)
		{
			printf("full cmd = %s\n", tmp_exec->full_cmd);
			tmp_exec = tmp_exec->next;
			i++;
		}
		tmp_exec = data.exec;
		i = 0;
		while (tmp_exec != NULL)
		{
			i = 0;
			while (tmp_exec->split_cmd[i] != NULL)
			{
				printf("split cmd = %s\n", tmp_exec->split_cmd[i]);
				i++;
			}
			tmp_exec = tmp_exec->next;
		}
		tmp_exec = data.exec;
		i = 0;
		tmp_exec = data.exec;
		i = 0;
		//free_bf_newprompt(&data);
//	}
	exit_free(&data, 0); //tmp
}

*/

/*
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	i = 0;
	//while (1)
	//{
		init_data(&data, envp);
		//get_input(&data);
		data.cmdline = ft_strdup(">>>>>>>");
		lexer(&data);
		expands(&data);
		parser(&data);
}
*/
