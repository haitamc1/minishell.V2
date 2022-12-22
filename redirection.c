/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:46:16 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/20 05:28:24 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	fake_herdoc(char	*delemeter)
{
	char	*string;

	string = readline("herdoc >: ");
	while (ft_strcmp(string, delemeter) && string)
		string = readline("herdoc >: ");
}

void	herdoc(char	*delemeter, int fd)
{
	char	*string;

	string = readline("heredoc >: ");
	while (ft_strcmp(string, delemeter) && string)
	{
		ft_putstr_fd(string, fd);
		ft_putstr_fd("\n", fd);
		string = readline("heredoc >:");
	}
}
// cat <<""'    '""ko<<""''"'" < zebzabi

void	extande_heredoc(char *buf)
{
	int		i;
	char	*name;

	i = 0;
	while (first_heredoc(buf, 1) != -1)
	{
		i = first_heredoc(buf, 1);
		name = redirection_name(ft_strdup(buf + i + 2));
		buf = exlude_name(buf, i, 2);
		fake_herdoc(name);
	}
}

char	*get_redi(t_arg *command)
{
	char	*buf;
	t_arg	*iter;

	iter = command;
	buf = ft_strdup("");
	while (iter)
	{
		if (iter->redirection)
		{
			buf = join_free(buf, iter->arg);
			buf = join_free(buf, " ");
			del_arg(&command, iter);
		}
		iter = iter->next;
	}
	return (buf);
}

// files_count it opens the directory and read all of it files
// count it and  return it
int	files_count(void)
{
	struct dirent	*file_dir;
	DIR				*dir;
	int				i;

	i = 0;
	dir = opendir("/tmp/");
	if (!dir)
	{
		write(2, "Opendir issue\n", 14);
		return (0);
	}
	file_dir = readdir(dir);
	if (!file_dir)
		return (0);
	while (file_dir)
	{
		file_dir = readdir(dir);
		i++;
	}
	closedir(dir);
	return (i);
}
