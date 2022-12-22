/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:48:45 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 11:13:38 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_qoutes_splited(char	**buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		buf[i] = eraseqout(buf[i], markqout(buf[i]));
		if (!buf[i])
			return (NULL);
		i++;
	}
	return (buf);
}

void	cmd(t_arg *arg, t_env **env)
{
	char	**splited;

	splited = joincmd(arg);
	if (!splited)
		return (ft_putstr_fd("error allocation", 2), exit(1));
	if (!splited[0])
		exit(1);
	if (!splited[0][0])
		return (ft_putstr_fd("command not found\n", 2), exit(127));
	if (if_directory(splited[0]))
		return (free_dp(splited), exit (126));
	else
	{
		if (!g_var.paths)
			no_path(splited);
		if (splited[0][0] == '/')
			binary_file(splited, env);
		else
			check_for_binaries(splited, env);
	}
	free_dp(splited);
	exit(127);
}

int	istherepipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 1)
			i += ignore_alpha(s + i, 1);
		if (s[i] == '|' && !is_quoted(s, s + i))
			return (i);
		i++;
	}
	return (-1);
}

void	executables(char *buf, t_env **env_p)
{
	int	pid;

	g_var.exit_status = 0;
	pid = fork();
	if (pid == -1)
		printf("\033[0;31mUnable to create processe\n");
	else
	{
		if (pid == 0)
			cmd(get_args(buf, env_p), env_p);
		else
		{
			sig_init();
			waitpid(pid, &(g_var.exit_status), 0);
			check_exit_status(pid);
		}
	}
}

void	execute2(char *buf, t_env **env_p)
{
	t_arg	*arg;
	char	*file;

	file = NULL;
	arg = get_args(buf, env_p);
	if (isthereredirection(arg))
	{
		file = get_file_names();
		redirection(arg, buf, env_p);
	}
	else if (!built_in(buf, env_p, arg))
		;
	else
		executables(buf, env_p);
	unlink(file);
	free(file);
	free(buf);
}
