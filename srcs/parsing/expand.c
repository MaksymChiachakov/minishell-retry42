/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoses <fmoses@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:48:35 by fmoses            #+#    #+#             */
/*   Updated: 2026/02/14 14:08:24 by fmoses           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(t_env *e, char *name, int len)
{
	char	*name_str;
	char	*value;

	if (len == 0)
		return (ft_strdup("$"));
	name_str = ft_substr(name, 0, len);
	if (ft_strncmp(name_str, "?", 1) == 0 && len == 1)
		return (free(name_str), ft_itoa(e->code_exit));
	value = find_env_var(e, name_str, len);
	free(name_str);
	if (value)
		return (value);
	return (ft_strdup(""));
}

void	expand_variable(t_env *e, char **s, t_token *t, int iq)
{
	int		len;
	char	*value;

	t->str++;
	if (*t->str == '?')
		len = 1;
	else
	{
		len = 0;
		while (ft_isalnum(t->str[len]) || t->str[len] == '_')
			len++;
		if (len == 0)
		{
			ft_concat(s, "$", !((t->str[len] == '"' && !iq)
					|| t->str[len] == '\''));
			return ;
		}
	}
	value = get_var_value(e, t->str, len);
	if (value)
	{
		ft_concat(s, value, -1);
		free(value);
	}
	t->str += len;
}

void	expand_quote(t_env *e, char **s, t_token *t, char quote)
{
	(void)e;
	t->str++;
	while (*t->str && *t->str != quote)
	{
		if (*t->str == '$' && quote == '\"')
			expand_variable(e, s, t, true);
		else
			ft_concat(s, t->str++, 1);
	}
	t->str++;
}

void	expand_home(t_env *e, char **s, t_token *t)
{
	char	*home;

	home = get_env_value("HOME", e);
	t->str++;
	ft_concat(s, home, -1);
	free(home);
}

char	*expand(t_env *e, t_token t)
{
	char	*s;
	char	*end;

	s = ft_calloc(8, sizeof(char));
	if (!s)
		return (NULL);
	if (t.str[0] == '~' && (!t.str[1] || t.str[1] == '/'))
		expand_home(e, &s, &t);
	end = t.str + t.len;
	while (t.str != end)
	{
		if (*t.str == '$')
			expand_variable(e, &s, &t, false);
		else if (*t.str == '\'' || *t.str == '"')
			expand_quote(e, &s, &t, *t.str);
		else
			ft_concat(&s, t.str++, 1);
	}
	return (s);
}
