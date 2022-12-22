/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_buf2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:36:12 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:40:03 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *buf, t_env **env)
{
	t_expnd	c;

	c = ds(0, 0, NULL);
	while (buf[c.i])
	{
		if (is_there_exitstat_check(buf, c.i))
			c.i = replace_exit_status(&buf, c.i);
		if (buf[c.i] == '$' && buf[c.i + 1] && buf[c.i + 1] != ' ')
			buf = replace_var(buf, c, env);
		c.i++;
	}
	return (buf);
}

char	*replace_wild_card(char *buf, t_expnd c, char *wild)
{
	char	*wild_free;

	wild_free = buf;
	buf = ft_strjoin(buf, wild);
	free(wild_free);
	wild_free = buf;
	buf = ft_strjoin(buf, wild_free + c.i + 1);
	free(wild_free);
	return (buf);
}

char	*full_replace_env(char *buf, t_env **env)
{
	char	*wild;
	t_expnd	c;

	c = ds(0, 0, NULL);
	while (buf[c.i])
	{
		if (is_there_exitstat_check(buf, c.i))
			c.i = replace_exit_status(&buf, c.i);
		if (buf[c.i] == '$' && buf[c.i + 1] && buf[c.i + 1] != ' ')
			buf = replace_var(buf, c, env);
		if (buf[c.i] == '*' && c.i == 0
			&& (is_space(buf[c.i + 1]) || !buf[c.i + 1])
			&& !is_quoted(buf, &buf[c.i]))
		{
			wild = wildcard();
			buf[c.i] = '\0';
			buf = replace_wild_card(buf, c, wild);
			c.i += ft_strlen(wild);
			free(wild);
		}
		c.i++;
	}
	return (buf);
}
