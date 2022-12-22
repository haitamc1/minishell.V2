/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:48:39 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:51:12 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *buf, t_env **env_p)
{
	int	pipecheck;

	sig_default();
	pipecheck = istherepipe(buf);
	if (pipecheck != -1)
	{
		do_pipe(buf, env_p);
		free(buf);
		return (0);
	}
	execute2(buf, env_p);
	sig_init();
	return (0);
}

int	execute_pipe(char *buf, t_env **env_p)
{
	if (!built_in(buf, env_p, get_args(buf, env_p)))
		;
	else
		cmd(get_args(buf, env_p), env_p);
	free(buf);
	return (0);
}

int	execute_redirection_pipe(char *buf, t_env **env_p, char *file, t_arg *arg)
{
	if (!buf)
		return (0);
	if (!built_in(buf, env_p, arg))
		;
	else
		cmd(get_args(buf, env_p), env_p);
	(void)file;
	free(buf);
	exit (0);
	return (0);
}

int	execute_redirection(char *buf, t_env **env_p, char *file)
{
	int	pid;

	(void)file;
	if (!buf)
		return (0);
	if (!built_in(buf, env_p, get_args(buf, env_p)))
		;
	else
	{
		g_var.exit_status = 0;
		pid = fork();
		if (pid == -1)
			return (printf("\033[0;31mUnable to create processe\n"));
		else
		{
			if (pid == 0)
				cmd(get_args(buf, env_p), env_p);
			else
			{
				waitpid(pid, &(g_var.exit_status), 0);
				check_exit_status(pid);
			}
		}
	}
	return (unlink(file), free(buf), 0);
}

char	*join_list(t_arg *cmd)
{
	char	*buf;
	t_arg	*iter;

	iter = cmd;
	if (!cmd)
		return (NULL);
	if (iter->linked)
		buf = ft_strdup(iter->arg);
	else
		buf = ft_strjoin(iter->arg, " ");
	iter = iter->next;
	while (iter)
	{
		buf = join_free(buf, iter->arg);
		if (!iter->linked && iter->next)
			buf = join_free(buf, " ");
		if (!buf)
			return (NULL);
		iter = iter->next;
	}
	delete_arg(cmd);
	return (buf);
}
