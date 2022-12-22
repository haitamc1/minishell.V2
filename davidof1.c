/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   davidof1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:13:50 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:14:25 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	is_empty(char	*str)
{
	int	i;

	i = 0;
	if (str[i] == '"' && str[i + 1] == '"')
		return (1);
	else if (str[i] == '\'' && str[i + 1] == '\'')
		return (1);
	return (0);
}
