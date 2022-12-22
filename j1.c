/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j1.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:21:34 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:21:54 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	still_in_name(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	closing_quote(char *line, char quote, int i)
{
	while (line[i] != quote)
		i++;
	i++;
	return (i);
}

int	quoted_heredoc(char *s, int i)
{
	if (s[i] == '<' && !is_quoted(s, s + i))
		return (1);
	return (0);
}
