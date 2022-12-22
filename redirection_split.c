/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:24:17 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:33:04 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*c;
	char	*p;

	i = 0;
	p = (char *)s1;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	c = malloc((i + 1) * sizeof(char));
	if (!c)
		return (0);
	i = 0;
	while (p[i])
	{
		c[i] = p[i];
		i++;
	}	
	c[i] = '\0';
	return (c);
}

int	is_quoted(char *s, char *mark)
{
	char	quote;
	int		i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && (s + i) > mark)
			return (0);
		else if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
			{
				if ((s + i) == mark)
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	isthereredirection(t_arg *s)
{
	t_arg	*iter;

	iter = s;
	while (iter)
	{
		if (iter->redirection)
			return (1);
		iter = iter->next;
	}
	return (0);
}

int	first_redirection(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if ((s[i] == '<' || s[i] == '>') && !is_quoted(s, s + i))
			return (i);
		i++;
	}
	return (-1);
}

int	redirection_count(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (first_redirection(s + i) != -1)
	{
		i += first_redirection(s + i);
		while (s[i] && (s[i] == '<' || s[i] == '>'))
			i++;
		count++;
	}
	return (count);
}
