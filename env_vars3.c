/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:19:40 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:20:33 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pre_dir(void)
{
	char	*tmp;
	int		i;

	i = 0;
	while (g_var.pwd[i])
		i++;
	if (g_var.pwd[i - 1] == '/')
		i--;
	while (g_var.pwd[i] != '/')
		i--;
	g_var.pwd[i] = '\0';
	tmp = ft_strdup(g_var.pwd);
	g_var.pwd[i] = 'l';
	free(g_var.pwd);
	g_var.pwd = ft_strdup (tmp);
	free(tmp);
}

void	join_err_pwd(char *dir)
{
	char	*r;
	int		i;
	int		j;

	i = ft_strlen(g_var.err_pwd);
	j = ft_strlen(dir);
	if (g_var.err_pwd[i - 1] != '/')
		r = malloc ((i + j + 2) * sizeof(char));
	else
		r = malloc ((i + j + 1) * sizeof(char));
	if (!r)
	{
		perror(r);
		return ;
	}
	ft_memcpy(r, g_var.err_pwd, i);
	if (g_var.err_pwd[i - 1] != '/')
		r[i++] = '/';
	r[i] = 0;
	r = join_free(r, dir);
	free(g_var.err_pwd);
	g_var.err_pwd = r;
}

int	count_backing(char *dir)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (dir[i])
	{
		if ((dir[i] && dir[i] == '.') && (dir[i + 1] == '.' && dir[i + 1])
			&& ((dir[i + 2] == '/' && dir[i + 2]) || !dir[i + 2]))
		{
			count++;
			i += 3;
		}
		else if ((dir[i] && dir[i] == '.')
			&& ((dir[i + 1] && dir[i + 1] == '/') || !dir[i + 1]))
			i += 2;
	}
	return (count);
}
