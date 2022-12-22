/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_args1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:41:59 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:44:45 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_arg_sq(char *arg)
{
	char	*tmp;

	if (arg[0] == '\'')
	{
		tmp = arg;
		arg = ft_substr(arg, 1, ft_strlen(arg) - 2);
		free(tmp);
	}
	return (arg);
}

char	*new_arg_dq(char *arg, t_env **env_p, t_star s, t_arg *r)
{
	char	*tmp;

	if (arg[0] == '"')
	{
		tmp = arg;
		arg = ft_substr(arg, 1, ft_strlen(arg) - 2);
		free(tmp);
		arg = replace_env(arg, env_p);
	}
	else
	{
		if (!ft_strcmp(arg, "*") && wildcardcheck(r, last_arg(r))
			&& after_star(s))
		{
			arg = full_replace_env(arg, env_p);
		}
		else
		{
			arg = replace_env(arg, env_p);
		}
	}
	return (arg);
}

t_arg	*new_arg(t_env **env_p, t_arg *r, t_star s, char linked)
{
	t_arg	*new;
	char	*arg;

	(void)env_p;
	arg = s.arg;
	new = malloc (sizeof(t_arg));
	if (!new || !arg)
		return (new);
	new->linked = linked;
	new->redirection = s.is_rediraction;
	if (arg[0] == '\'' || is_redirection(arg[0]))
		arg = new_arg_sq(arg);
	else
		arg = new_arg_dq(arg, env_p, s, r);
	new->arg = arg;
	new->next = NULL;
	return (new);
}

int	add_back_arg(t_arg **lst, t_arg *new)
{
	t_arg	*iter;

	iter = *lst;
	if (!new)
		return (1);
	if (*lst == NULL)
		*lst = new;
	else
	{
		last_arg(iter)->next = new;
	}
	return (0);
}

int	quoted_redirection(char *s, int i)
{
	if ((s[i] == '<' || s[i] == '>') && !is_quoted(s, s + i))
		return (1);
	return (0);
}
