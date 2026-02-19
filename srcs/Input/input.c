/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <mchiacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:35:35 by mchiacha          #+#    #+#             */
/*   Updated: 2026/02/19 15:37:31 by mchiacha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"


#define RESET "\001\033[0m\002"
#define BOLD_RED "\001\033[1;31m\002"
#define BOLD_WHITE "\001\033[1;37m\002"

char	*bpromt(void)
{
	const char	*u_name;
	char		*promt;
	size_t		len;

	u_name = getenv("USER");
	if (!u_name)
		u_name = "user";
	len = ft_strlen(BOLD_WHITE) + ft_strlen(u_name) + ft_strlen(RESET)
		+ ft_strlen(BOLD_RED) + ft_strlen("@") + ft_strlen(RESET)
		+ ft_strlen(BOLD_RED) + ft_strlen("minishell> ") + ft_strlen(RESET);
	promt = malloc(sizeof(char) * (len + 1));
	if (!promt)
		return (NULL);
	ft_strcpy(promt, BOLD_WHITE);
	ft_strcat(promt, (char *)u_name);
	ft_strcat(promt, RESET);
	ft_strcat(promt, BOLD_RED);
	ft_strcat(promt, "@");
	ft_strcat(promt, "minishell> ");
	ft_strcat(promt, RESET);
	return (promt);
}

char	*read_inter_line(void)
{
	char	*promt;
	char	*line;

	promt = bpromt();
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

int	main_supp_sec(void)
{
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	return (0);
}
