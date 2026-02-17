/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:32:01 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/17 17:29:45 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	free_shell(t_env *env)
{
	if (!env)
		return ;
	if (env->envp)
	{
		free_env(env->envp);
		env->envp = NULL;
	}
	clear_command(env);
	clear_history();
	rl_clear_history();
}

void	fexit(t_env *env, int code)
{
	free_shell(env);
	exit(code);
}

int	is_all_whitepace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_whitespace(str[i]))
			return (false);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	ctx;

	(void)argc;
	(void)argv;
	ft_memset(&ctx, 0, sizeof(t_env));
	ctx.envp = ft_copy_env(envp);
	if (!ctx.envp)
		return (ft_printf("Error: Failed to copy environment\n"), 1);
	ctx.code_exit = 0;
	ctx.should_exit = false;
	setup_signals();
	while (ctx.should_exit == false)
	{
		ctx.command = read_input_line();
		if (!ctx.command)
		{
			if (isatty(STDIN_FILENO)) // Ctrl + D
				write(1, "exit\n", 5);
			break ;
		}
		if (!is_all_whitepace(ctx.command))
		{
			add_history(ctx.command);
			execute_commands(&ctx);
		}
		free(ctx.command);
	}
	return (free_shell(&ctx), ctx.code_exit);
}
