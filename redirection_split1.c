/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:32:48 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:34:36 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redirection_name(char *buf)
{
	int		i;
	char	*name;
	int		start;

	i = 0;
	while (buf[i] != 1 && buf[i])
		i++;
	if (buf[i] == 1)
		start = ++i;
	while (buf[i] != 1 && buf[i])
		i++;
	if (buf[i] == 1)
	{
		buf[i] = '\0';
	}
	name = ft_strdup(buf + start);
	return (name);
}

// end 2 means exlude redirection and delemeter 
// end 0 means exclude only rederaction and remove special character
char	*exclude_name1(char *str, int start, int i, char *new)
{
	str[start] = '\0';
	start++;
	i = start;
	while (str[start] != 1 && str[start])
		start++;
	if (str[start] == 1)
		str[start] = ' ';
	while (str[start] != 1 && str[start])
		start++;
	if (str[start] == 1)
		str[start] = ' ';
	new = ft_strdup(str);
	new = ft_strjoin(new, " ");
	new = ft_strjoin(new, str + i);
	return (new);
}

char	*exlude_name(char	*str, int start, int end)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	if (end == 2)
	{
		str[start] = '\0';
		start++;
		while (str[start] != 1 && str[start])
			start++;
		start++;
		while (str[start] != 1 && str[start])
			start++;
		new = ft_strdup(str);
		new = ft_strjoin(new, str + start + 1);
	}
	else if (end == 0)
		new = exclude_name1(str, start, i, new);
	free(str);
	return (new);
}

int	first_heredoc(char *s, int hd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if ((s[i] == '<' && s[i + 1] == '<') && !is_quoted(s, s + i))
			return (i);
		else if ((s[i] == '<' && s[i + 1] != '<' && s[i - 1] != '<')
			&& !is_quoted(s, s + i) && hd == 2)
			return (i);
		i++;
	}
	return (-1);
}

int	outputcheck(char *s, int hd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if ((s[i] == '>' && s[i + 1] == '>') && !is_quoted(s, s + i))
			return (i);
		else if ((s[i] == '>' && s[i + 1] != '>' && s[i - 1] != '>')
			&& !is_quoted(s, s + i) && hd == 2)
			return (i);
		i++;
	}
	return (-1);
}
