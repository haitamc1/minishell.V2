/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:18:15 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/20 05:19:57 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_evar_value(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->e_name))
			return (env->e_value);
		env = env->next;
	}
	return (NULL);
}

int	arg_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	remove_path(void)
{
	char	**tmp;

	tmp = g_var.paths;
	while (*tmp)
		free(*tmp++);
	free(g_var.paths);
	g_var.paths = NULL;
}

void	display_with_declare(t_env *p)
{
	while (p)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((p->e_name), 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd((p->e_value), 1);
		ft_putstr_fd("\n", 1);
		p = p->next;
	}
}

int	valid_export(char *s)
{
	char	*p;

	p = NULL;
	p = ft_strchr(s, '=');
	if (!p || s[0] == '=' || s[0] == '+')
	{
		if (!p && !ft_strchr(s, '+'))
			return (0);
		ft_putstr_fd("invalid identifier\n", 2);
		return (0);
	}
	if (*(p - 1) == '+' && *(p - 2) == '+')
	{
		ft_putstr_fd("invalid identifier\n", 2);
		return (0);
	}
	if (!ft_isalnum(*(p - 1)) && *(p - 1) != '+')
	{
		ft_putstr_fd("invalid identifier\n", 2);
		return (0);
	}
	return (1);
}
