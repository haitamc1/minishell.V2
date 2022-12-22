/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:15:58 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:16:25 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_e_var_value(char *value)
{
	char	*ret;
	int		i;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	i++;
	ret = ft_strdup(value + i);
	return (ret);
}

void	release_e_var(t_env **env_p)
{
	t_env	*iter;
	t_env	*tmp;

	iter = *env_p;
	if (!env_p || !*env_p)
		return ;
	while (iter)
	{
		tmp = iter;
		iter = iter->next;
		free(tmp->e_name);
		free(tmp->e_value);
		free(tmp);
	}
}

void	update_pwd_env(t_env **env_p, char *old_pwd, char *new_pwd)
{
	t_env	*iter;

	iter = *env_p;
	if (!new_pwd || !old_pwd)
		return ;
	while (iter)
	{
		if (!ft_strncmp(iter->e_name, "PWD"
				, ft_strlen (iter->e_name) + ft_strlen("PWD")))
			update_pwd_vars(&(iter->e_value), new_pwd);
		else if (!ft_strncmp(iter->e_name, "OLDPWD"
				, ft_strlen (iter->e_name) + ft_strlen("OLDPWD")))
			update_pwd_vars(&(iter->e_value), old_pwd);
		iter = iter->next;
	}
}
