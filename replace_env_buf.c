/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_buf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:33:26 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/20 05:36:28 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sub_str(char *s, int start, int end)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc (end - start + 1);
	if (!p)
		perror (p);
	while (start <= end)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

char	*remove_arg(char *buf, int start, int end)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc (ft_strlen(buf) - (end - start + 2));
	if (!ret)
		return (NULL);
	while (i < start - 1)
	{
		ret[i] = buf[i];
		i++;
	}
	j = i;
	i = end + 1;
	while (buf[i])
		ret[j++] = buf[i++];
	ret[j] = '\0';
	return (ret);
}

int	env_exist(t_env **env_p, char *name)
{
	t_env	*iter;

	iter = *env_p;
	if (!env_p || !iter)
		return (0);
	while (iter)
	{
		if (!ft_strcmp(name, iter->e_name))
			return (1);
		iter = iter->next;
	}
	return (0);
}

// char	*expand_it(char *buf, char *tmp, int start, int end, t_env **env_p)
char	*expand_it(char *buf, t_expnd c, t_env **env_p)
{
	char	*ret;
	char	*env;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	c.i--;
	env = extract_evar_value(*env_p, c.tmp);
	len = ft_strlen (buf) + c.i - c.index + 1 + ft_strlen (env);
	ret = malloc (len + 1);
	if (!ret)
		return (NULL);
	while (++i < c.index - 1)
		ret[i] = buf[i];
	while (env[j])
		ret[i++] = env[j++];
	j = c.i + 1;
	while (buf[j])
		ret[i++] = buf[j++];
	ret[i] = '\0';
	return (ret);
}

char	*replace_exstat_val(char *buf, int start, int finish)
{
	char	*r;

	buf[start] = 0;
	r = ft_strdup(buf);
	if (!r)
		return (perror(r), NULL);
	r = join_free(r, ft_itoa(g_var.exit_status));
	if (!r)
		return (perror(r), NULL);
	r = join_free(r, buf + finish);
	if (!r)
		return (perror(r), NULL);
	return (r);
}
