/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:17:56 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:19:04 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_malloc_msg(void)
{
	ft_putstr_fd("Error occur with allocation\n", 2);
}

char	**get_cmd_arg_size(char *buf)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	ret = malloc(sizeof (char *) * 2);
	if (!ret)
		return (err_malloc_msg(), NULL);
	ret[0] = malloc (i);
	if (!ret[0])
		return (err_malloc_msg(), free(ret), NULL);
	while (is_space(buf[i]) && buf[i])
		i++;
	while (buf[i++])
		j++;
	ret[1] = malloc (j + 1);
	if (!ret[1])
		return (err_malloc_msg(), free(ret[0]), free(ret), NULL);
	return (ret);
}

char	**cmd_arg(char *buf)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = get_cmd_arg_size(buf);
	if (!ret)
		return (NULL);
	while (buf[i] && buf[i] != ' ')
	{
		ret[0][i] = buf[i];
		i++;
	}
	ret[0][i] = '\0';
	while (is_space(buf[i]) && buf[i])
		i++;
	while (buf[i])
		ret[1][j++] = buf[i++];
	ret[1][j] = '\0';
	return (ret);
}

char	*get_pwd_evar(t_env *p)
{
	if (!p)
		return (NULL);
	while (p)
	{
		if (!ft_strncmp("PWD", p->e_name, 4))
			return (p->e_value);
		p = p->next;
	}
	return (NULL);
}

char	*get_less_pwd_evar(t_env *p)
{
	char	*s;
	int		i;

	i = 0;
	if (!p)
		return (NULL);
	while (p)
	{
		if (!ft_strncmp("PWD", p->e_name, 4))
		{
			s = ft_strdup(p->e_value);
			while (s[i])
				i++;
			while (s[i] != '/')
				i--;
			s[i] = '\0';
			return (s);
		}
		p = p->next;
	}
	return (NULL);
}
