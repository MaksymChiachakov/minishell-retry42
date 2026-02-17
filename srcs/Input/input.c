/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:35:35 by mchiacha          #+#    #+#             */
/*   Updated: 2026/01/14 21:58:48 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BOLD_WHITE "\001\033[1;37m\002"
#define BOLD_RED "\001\033[1;31m\002"
#define RESET "\001\033[0m\002"

char	*build_promt(void)
{
	const char	*username;
	char		*prompt;
	size_t		len;

	username = getenv("USER");
	if (!username)
		username = "user";
	len = ft_strlen(BOLD_WHITE) + ft_strlen(username) + ft_strlen(RESET)
		+ ft_strlen(BOLD_RED) + ft_strlen("@") + ft_strlen(RESET)
		+ ft_strlen(BOLD_RED) + ft_strlen("minishell> ") + ft_strlen(RESET);
	prompt = malloc(sizeof(char) * (len + 1));
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, BOLD_WHITE);
	ft_strcat(prompt, (char *)username);
	ft_strcat(prompt, RESET);
	ft_strcat(prompt, BOLD_RED);
	ft_strcat(prompt, "@");
	ft_strcat(prompt, "minishell> ");
	ft_strcat(prompt, RESET);
	return (prompt);
}

static char	*read_inter_line(void)
{
	char	*promt;
	char	*line;

	promt = build_promt();
	if (!promt)
		return (NULL);
	line = readline(promt);
	return (free(promt), line);
}

static char	*read_non_inter_line(void)
{
	size_t	len;
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (line)
	{
		len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	return (line);
}

char	*read_input_line(void)
{
	if (isatty(STDIN_FILENO))
		return (read_inter_line());
	else
		return (read_non_inter_line());
}
