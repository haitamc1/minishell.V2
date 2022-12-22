/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 19:47:55 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:44:44 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "minishell.h"

t_arg	*last_arg(t_arg *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	delete_arg(t_arg *p)
{
	t_arg	*iter;

	while (p)
	{
		iter = p;
		p = p->next;
		free(iter->arg);
		free(iter);
	}
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	wildcardcheck(t_arg *r, t_arg *node)
{
	t_arg	*iter;
	int		check;

	check = 0;
	iter = r;
	if (!r)
		return (check);
	if (!node->linked)
		return (1);
	if (node->linked && !ft_strcmp(node->arg, ""))
	{
		while (iter->next != node)
			iter = iter->next;
		check = wildcardcheck(r, iter);
	}
	else if (node->linked && ft_strcmp(node->arg, ""))
		return (check);
	if (!check)
		return (check);
	return (1);
}

// t_arg	*new_arg(char *arg, char linked)

int	after_star(t_star s)
{
	int	i;

	i = s.index + 1;
	while (s.buf[i])
	{
		if (is_empty(s.buf + i))
			i += 2;
		else if (is_space(s.buf[i]))
			return (1);
		else
			return (0);
	}
	return (1);
}
