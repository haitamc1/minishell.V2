/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_buf1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:35:46 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:36:03 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_exit_status(char **buf, int i)
{
	char	*hold;

	hold = *buf;
	*buf = replace_exstat_val(*buf, i, i + 2);
	i += ft_strlen(ft_itoa(g_var.exit_status));
	free(hold);
	return (i);
}

int	cut_false_env(char **buf, int i, int index)
{
	char	*hold;

	hold = *buf;
	*buf = remove_arg(*buf, index, i - 1);
	i = index - 1;
	free(hold);
	return (i);
}

int	is_there_exitstat_check(char *buf, int i)
{
	if (buf[i] == '$' && buf[i + 1] == '?'
		&& (!ft_isalnum(buf[i + 2]) || buf[i + 2] != '_'))
		return (1);
	return (0);
}

t_expnd	ds(int i, int index, char *tmp)
{
	t_expnd	s;

	s.i = i;
	s.index = index;
	s.tmp = tmp;
	return (s);
}

// void	init_expnd()

char	*replace_var(char *buf, t_expnd c, t_env **env)
{
	char	*hold;

	hold = NULL;
	c.i++;
	c.index = c.i;
	while (buf[c.i] && (ft_isalnum(buf[c.i]) || buf[c.i] == '_'))
		c.i++;
	c.tmp = sub_str(buf, c.index, c.i - 1);
	if (!c.tmp)
		return (perror(c.tmp), NULL);
	else if (env_exist(env, c.tmp))
	{
		hold = buf;
		buf = expand_it(buf, c, env);
		c.i = c.index;
		c.i += ft_strlen(extract_evar_value(*env, c.tmp));
		free(hold);
	}
	else
		c.i = cut_false_env(&buf, c.i, c.index);
	free(c.tmp);
	c.i -= 1;
	return (buf);
}
