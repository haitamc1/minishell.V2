/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:42:23 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/20 22:52:52 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *s)
{
	int	i;

	i = 1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	fecho(char **s, t_arg *arg)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	(void)arg;
	while (s[i])
	{
		if (!flag && (s[i][0] == '-') && check_option(s[i]))
		{
			flag = 1;
			i++;
			continue ;
		}
		else
		{
			ft_putstr_fd(s[i], STDOUT_FILENO);
			write(1, " ", 1);
		}
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
