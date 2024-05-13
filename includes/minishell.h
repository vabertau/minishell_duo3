#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libftprintf/ft_printf.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int			g_signal_count;

typedef enum s_type
{
	WORD,
	PIPE,
	RIGHT1,
	RIGHT2,
	LEFT1,
	LEFT2,
	DQUOTE,
}					t_type;

typedef struct s_env
{
	int				index;
	char			**first_env;
	char			*var;
	char			*var_name;
	char			*val;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	int				i;
	char			*word;
	t_type			type;
	int				fd;
	struct s_token	*next;
}					t_token;

typedef struct s_exec
{
	char			*full_cmd;
	char			**split_cmd;
	int				nb_redir;
	pid_t			pid;
	t_token			*redir;
	struct s_exec	*next;
}					t_exec;

typedef struct s_data
{
	char			*cmdline;
	int				nb_tokens;
	int				nb_sq;
	int				nb_dq;
	int				nb_cmd;
	int				*pipe_fds;
	t_token			*token;
	t_type			type;
	t_exec			*exec;
	t_env			*env;
	char			**char_env;
	char			**envp;
	int				*is_bq;
	int				last_pid;
	int				last_return_code;
	bool			spec_built;
	bool			sh_exit_loop;
	bool			void_expand;
}					t_data;

// ====== READLINE ======

void				get_input(t_data *data);

// ====== INIT_DATA ======

void				init_data(t_data *data);

// ===== CHECKER =====

int					check_unclosedq(t_data *data);
void				parsing_error(t_data *data);
void				checks(t_data *data);
void				check_schar_error(t_data *data);
void				check_pipe_ext(t_data *data);
void				check_empty(t_data *data);
int					check_for_append_space_append(t_data *data);

// ===== CHECKER AFTER REDIR =====

void				check_redirfile(t_data *data);

// ====== LEXER ======

void				lexer(t_data *data);
void				nb_tokens(t_data *data);
int					spaces_bet_tokens(t_data *data);
int					skip_sq(char *cmdline);
int					skip_dq(char *cmdline);
void				malloc_tokens(t_data *data);
void				fill_tokens(t_data *data);
char				**ft_quotesplit(t_data *data, char const *s);
int					copy_bet_sq(int *i, int *j, const char *s, char *tmp);
int					copy_bet_dq(int *i, int *j, const char *s, char *tmp);
void				fill_types(t_data *data);

// ===== PARSER =====

void				nb_cmd(t_data *data);
void				parser(t_data *data);
void				malloc_exec(t_data *data);
void				fill_full_cmd(t_data *data);
void				fill_split_cmd(t_data *data);
void				nb_redir(t_data *data);
void				fill_redir(t_data *data);
void				init_exec(t_data *data);
int					fixed_cmdline_len(char *cmdline);
int					nb_chains(char const *s, char c);
int					first_nonc(char const *s, char c, int i);

// ===== EXPANDS =====

int					expands(t_data *data);
bool				is_to_expand(char *word);
void				replace_var(t_data *data, char **word, int i, int len_var);
char				*fetch_var_content(t_data *data, char *var, char **env);

// ====== EXIT ======

void				exit_free(t_data *data, int exit_code);
void				free_bf_newprompt(t_data *data);
void				set_exitloop_free(t_data *data);
void				free_all(t_data *data);
void				free_token(t_token *token);
void free_env(t_data *shell);

// ====== BUILTINS ======

int					ft_echo(char **split_cmd);

// ====== EXEC ======

char				*join_free1(char const *s1, char const *s2);

// Prototypes des fonctions de gestion de redirection
void				handle_input_redirection(t_token *redir, t_data *shell);
void				handle_output_redirection(t_token *redir, t_data *shell);
void				handle_here_document(t_token *redir, t_data *shell);
void				handle_append_redirection(t_token *redir, int fd,
						t_data *shell);
void				handle_redirections(t_exec *cmd, t_data *shell);
void				fill_redir_heredoc(t_data *shell, int *cpt, t_token *redir);
void				prepare_heredocs(t_data *shell);

// Prototypes des fonctions d'exécution de commandes
void				exec_cmd(t_data *shell, t_exec *cmd);
int					executor(t_data *shell);

// Prototype de la fonction de manipulation de chaînes et utilitaires
char				*join_free1(char const *s1, char const *s2);
char				*join_free2(char const *s1, char const *s2);
int					ft_same_str_free(char *str1, char *str2, size_t n);

// Prototype de la fonction de gestion des pipes
int					init_pipes(t_data *shell);

void				prepare_out2(t_data *shell);
void				prepare_out1(t_data *shell);

int					safe_open(const char *pathname, int flags, mode_t mode,
						t_data *shell);

void				safe_close(int fd, t_data *shell);
void				safe_dup2(int oldfd, int newfd, t_data *shell);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_same_str(char *str1, char *str2, size_t n);

// Prototype de la fonction de gestion des signaux
void				handle_sigint_interactive(int sig);
void				handle_sigint_heredoc(int sig);
void				handle_sigint_command(int sig);
void				handle_sigquit_command(int sig);
void				handle_sigquit(int sig);
void				setup_signal_handlers(void (*sigint_handler)(int),
						void (*sigquit_handler)(int));
void				exec_build(t_data *shell, char **f);
void				dup_pipe_child(t_data *shell, t_exec *cmd, int *i);
void				setup_heredoc_handlers(void);

int					ft_echo(char **split_cmd);
void				main_signals(void);
void				execute_signals(int pid);
int					return_if_sig(int status, int l);
void				heredoc_signals(void);

/* Function prototype for ft_cd */
int					ft_cd(char **split_cmd, t_data *data);

/* Function prototype for ft_pwd */
int					ft_pwd(t_data *data);

/* Function prototype for ft_export */
int					ft_same_str_exact_free1(char *str1, char *str2);
char				*ft_strndup_var(const char *s, int n);
char				**malloc_var(int i, char *s, int j, int n);
char				**split_var(char *s, t_data *shell);
int					find_index_env(char *env);
int					var_in_env(char *s, t_data *shell);
int					check_plus(char *s);
void				ft_update_env(char *str, t_data *shell, int pos);
void				ft_add_env(char *s, t_data *shell);
int					ft_putenv(char *s, t_data *shell);
void				ft_printf_var_env(char *var);
int					check_cmd(char *s);
int					ft_export(char **split_cmd, t_data *shell);
int					ft_unset(char **split_cmd);
int					ft_env(char **envp);

/* Function prototype for ft_exit */
int					ft_exit(char **split_cmd, t_data *data);
#endif
