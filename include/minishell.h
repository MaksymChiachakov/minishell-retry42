/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:32:01 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/19 14:44:54 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <termios.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_command
{
	char						**args;
	int							infd;
	int							outfd;
	struct s_command			*next;
	int							nextmode;
}								t_command;

typedef struct s_env
{
	char						**envp;
	int							code_exit;
	char						*command;
	int							index;
	char						**new_env;
	int							tmp_stdin;
	bool						should_exit;
	t_command					*cmd;
}								t_env;

typedef struct s_token
{
	int							kind;
	char						*str;
	int							len;
}								t_token;

enum							e_token_kind
{
	TOKEN_WORD = 0,
	TOKEN_OP = 1,
	TOKEN_EOF = 2,
};

# define ERROR 1111111111

/* lexer.c */
t_token							get_next_token(t_env *ctx);
t_token							peek_next_token(t_env *e);

/* parse.c */
t_command						*parse(t_env *e);

/* exec.c */
void							execute_commands(t_env *e);
void							handle_parent_signals(t_env *e, int status);
int								pipe_command(t_command *cmd);
int								execute_command(t_env *e, t_command *cmd);
void							execute_commands_supp(t_env *e, t_command *cmd);
void							handle_exec_end(t_env *e, int pid, int status);
void							process_command_pipeline(t_env *e);

/* expand.c */
char							*expand(t_env *e, t_token t);

/* heredoc.c */
int								heredoc(t_env *e, t_command *cmd);
int								heredoc_supp(t_env *e, char *line, struct sigaction *sa_old, int fds[2]);
void							heredoc_supp_sec(char *line, int fds[2]);
int								test_if(int fds[2], t_token *eof, t_env *e);
int								heredoc_supp_finish(t_command *cmd, int fds[2], struct sigaction *sa_old);
int								open_file(t_env *e, t_command *cmd, int flag);
void							handle_sigint_heredoc(int sig);
int								syntax_error(t_env *e, t_token t);
int								system_error(t_env *e, char *name);
void							setup_signals_heredoc(struct sigaction *old);

/* variables.c */
char							*find_env_var(t_env *e, char *name, int len);

/* strings.c */
int								is_whitespace(char c);
int								is_shell_operator(char c);
int								ft_concat(char **dst, char *src, int src_len);
char							*join_path(char *dir, char *file);
void							free_split(char **strs);

//
int								check_command_syntax(t_command *cmd);

/* arrays.c */
int								ft_arrlen(char **arr);
void							ft_append(char ***list, char *item);

/* building */
int								builtin_pwd(t_command *cmd);
int								is_builtin(char *cmd);
int								exec_builtin(t_command *cmd, t_env *env);
int								echo_build(t_command *cmd, char **argv);
int								ft_cd(t_command *cmd, t_env *env);
int								ft_exit(t_command *cmd, t_env *env);
int								ft_unset(t_command *cmd, t_env *env);
int								ft_export(t_command *cmd, t_env *shell);
int								ft_env(t_command *cmd, t_env *env);

/* input */
char							*read_input_line(void);

/* errors */
void							print_error(char *cmd, char *arg, char *error);
void							flag_error(t_env *e, char *cmd, char *arg,
									char *error);
void							check_execuable_error(t_env *e, char *bin);
void							fexit(t_env *env, int code);

/* env */
void							init_default_env(t_env *env);
char							*get_env_value(char *key, t_env *env);
char							**ft_copy_env(char **env);
void							set_env_value(char *key, const char *value,
									t_env *env);
void							remove_env_var(char *key, t_env *env);
int								is_valid_env_name(char *name);
void							free_env(char **env);
char							*find_env_var(t_env *e, char *name, int len);
int								update_env_value(char *var, int key_len, t_env *env);

/* command */
void							clear_command(t_env *e);
void							free_command(t_command *cmd);
t_command						*create_command(void);

/* signals */
void							setup_signals(void);
void	setup_signals_interactive(void);
void							handle_child_signals(void);
void							ignore_signals(void);
void							restore_signals(void);

#endif
