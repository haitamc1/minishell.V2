/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:48:48 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:49:12 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tab(t_env *env)
{
	char	**tab;
	t_env	*t;
	int		i;

	i = 0;
	t = env;
	while (env)
	{
		i++;
		env = env->next;
	}
	tab = malloc (sizeof(char *) * i);
	if (!tab)
		exit(0);
	i = 0;
	while (t)
	{
		tab[i] = ft_strjoin(ft_strjoin(t->e_name, "="), t->e_value);
		i++;
		t = t->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	no_path(char **splited)
{
	printf("\033[0;31m %s: No such file or directory\n", splited[0]);
	free_dp(splited);
	exit(127);
}

void	binary_file(char **splited, t_env **env)
{
	char	**tb;

	tb = list_to_tab(*env);
	execve(splited[0], splited, tb);
	execve(splited[0], splited, NULL);
	printf("\033[0;31m %s: No such file or directory\n", splited[0]);
	free_dp(splited);
	exit(127);
}

void	check_for_binaries(char **splited, t_env **env)
{
	char	**tb;
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strdup(splited[0]);
	free(splited[0]);
	while (g_var.paths[i])
	{
		splited[0] = ft_strjoin(g_var.paths[i], cmd);
		execve(splited[0], splited, NULL);
		free(splited[0]);
		i++;
	}
	splited[0] = ft_strjoin(g_var.pwd, "/");
	splited[0] = join_free(splited[0], cmd);
	tb = list_to_tab(*env);
	execve(splited[0], splited, tb);
	perror (cmd);
}

char	**prepar_tb_cmd(t_arg *arg)
{
	t_arg	*iter;
	int		i;
	char	**tb;

	i = 0;
	iter = arg;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	tb = malloc (sizeof(char *) * i + 1);
	if (!tb)
		return (ft_putstr_fd("failed to allocate \n", 2), NULL);
	iter = arg;
	i = 0;
	while (iter)
	{
		tb[i] = eraseqout(iter->arg, markqout(iter->arg));
		iter = iter->next;
		i++;
	}
	tb[i] = NULL;
	delete_arg(arg);
	return (tb);
}
