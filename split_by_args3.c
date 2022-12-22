/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_args3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:42:13 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 11:18:38 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*remove_qoutess(t_arg *comand)
{
	t_arg	*iter;
	char	special_string[2];

	iter = comand;
	special_string[0] = 1;
	special_string[1] = 0;
	while (iter)
	{
		if ((is_redirection(iter->arg[0])
				&& is_redirection(iter->arg[1]) && iter->arg[2])
			|| (is_redirection(iter->arg[0]) && iter->arg[1]))
			iter->arg = set_up_name(iter->arg, special_string);
		iter = iter->next;
	}
	return (comand);
}

int	get_heredoc_arg(char *buf, t_hold *c, t_star star, t_arg **r)
{
	c->i += end_of_name(buf + c->i);
	star.arg = ft_substr(buf, c->index, c->i - c->index + 1);
	star.is_rediraction = 1;
	if (add_back_arg(r, new_arg(c->env, *r, star, 0)))
		return (1);
	return (0);
}

int	get_normal_arg(char *buf, t_hold *c, t_star star, t_arg **r)
{
	int	check;

	check = 0;
	star.i = c->i;
	c->i += end_of_arg(buf + c->i);
	star.is_rediraction = 0;
	star.arg = ft_substr(buf, c->index, c->i - c->index + 1);
	if (buf[c->i + 1] && !is_space(buf[c->i + 1]))
		check = add_back_arg(r, new_arg(c->env, *r, star, 1));
	else
		check = add_back_arg(r, new_arg(c->env, *r, star, 0));
	return (check);
}

int	skip_space(char *buf, int i)
{
	while (is_space(buf[i]))
			i++;
	return (i);
}

t_arg	*get_args(char *s, t_env **env)
{
	t_star	star;
	t_arg	*r;
	t_hold	c;
	int		check;

	c.i = 0;
	c.env = env;
	r = NULL;
	star.buf = s;
	while (s[c.i])
	{
		c.i = skip_space(s, c.i);
		c.index = c.i;
		star.index = c.i;
		if (!s[c.i] || (c.i > (int)ft_strlen(s) - 1))
			break ;
		if (s[c.i] == '<' || s[c.i] == '>')
			check = get_heredoc_arg(s, &c, star, &r);
		else
			check = get_normal_arg(s, &c, star, &r);
		if (check)
			return (delete_arg(r), NULL);
		c.i++;
	}
	return (remove_qoutess(r));
}
