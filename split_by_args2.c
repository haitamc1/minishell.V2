/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_args2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:42:08 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:43:52 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_arg(char *s)
{
	char	hold;
	int		i;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		hold = s[i++];
		while (s[i] && s[i] != hold)
			i++;
		return (i);
	}
	while (s[i] && s[i] != '"' && s[i] != '\''
		&& !is_space(s[i]) && !is_redirection(s[i]))
		i++;
	if (s[i] == '"' || s[i] == '\'' || is_space(s[i]) || is_redirection(s[i]))
		i--;
	return (i);
}

int	end_of_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
		i++;
	while (is_space(s[i]))
			i++;
	while (s[i] && !quoted_space(s, i) && !quoted_redirection(s, i))
		i++;
	if (s[i])
		i--;
	return (i);
}

// t_arg	*last_arg(t_arg *lst);
// t_arg	*new_arg(char *arg, char type);
// int		add_back_arg(t_arg **lst, t_arg *new);

char	*new_name(char *name, int len)
{
	char	*r;
	int		i;

	i = 0;
	while (!name[i] && i < len)
				i++;
	if (i == len)
		return (ft_strdup(""));
	r = ft_strdup(name + i);
	while (name[i] && i < len)
		i++;
	while (i < len)
	{
		if (name[i])
		{
			r = join_free(r, name + i);
			while (name[i] && i < len)
				i++;
		}
		else
			i++;
	}
	return (r);
}

char	*empty_out(char *name)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name);
	while (i < len)
	{
		if (i < len && name[i] == '\'')
		{
			name[i++] = 0;
			while (name[i] && name[i] != '\'')
				i++;
			name[i++] = 0;
		}
		if (i < len && name[i] == '"')
		{
			name[i++] = 0;
			while (name[i] && name[i] != '"')
				i++;
			name[i++] = 0;
		}
		if (i < len && name[i] != '"' && name[i] != '\'')
			i++;
	}
	return (new_name(name, len));
}

char	*set_up_name(char *buf, char *special_string)
{
	char	*name;
	char	*tmp;
	char	hold;
	int		i;

	i = 0;
	while (is_redirection(buf[i]))
				i++;
	hold = buf[i - 1];
	buf[i - 1] = 0;
	while (is_space(buf[i]))
		i++;
	name = ft_strdup(buf + i);
	tmp = name;
	name = empty_out(name);
	free(tmp);
	i = 0;
	while (buf[i])
		i++;
	buf[i++] = hold;
	buf[i] = 0;
	buf = join_free(buf, special_string);
	buf = join_free(buf, name);
	buf = join_free(buf, special_string);
	return (free(name), buf);
}
