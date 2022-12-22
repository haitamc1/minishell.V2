/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:23:21 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:24:24 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_dir_files(int i)
{
	struct dirent	*file_dir;
	DIR				*dir;
	int				j;
	char			**files;

	j = 0;
	dir = opendir("/tmp/");
	if (!dir)
	{
		write(2, "Opendir issue\n", 14);
		return (NULL);
	}
	files = malloc(sizeof(char *) * i + 1);
	if (!files)
	{
		ft_putstr_fd("tableau de file names not allocated\n", 2);
		return (NULL);
	}
	file_dir = readdir(dir);
	while (file_dir)
	{
		files[j++] = file_dir->d_name;
		file_dir = readdir(dir);
	}
	return (files[j] = NULL, closedir(dir), files);
}

// it takes the 2D table that has the files names and check for
// .A if it exists it add A and keep looking until it finds a useable name
char	*get_right_file_names(char	**files, char *name)
{
	int		i;
	int		j;
	char	*extra;

	j = 0;
	i = 0;
	extra = ft_strdup("A");
	name = ft_strdup(".A");
	while (files[j])
	{
		if (ft_strcmp(files[j], name))
			j++;
		else
		{
			name = join_free(name, extra);
			i++;
			j = 0;
		}
	}
	free(extra);
	return (name);
}
// basicaly it reads all the files in the directory 
// check/generate heredoc files name
// in case of running multiple minishells

char	*get_file_names(void)
{
	char			*name;
	char			**files;
	int				i;
	char			*ex;

	name = NULL;
	i = files_count();
	files = get_dir_files(i);
	name = get_right_file_names(files, name);
	free(files);
	ex = name;
	name = ft_strjoin("/tmp/", name);
	free(ex);
	return (name);
}

// it exclude the redi nad its delemeter from the command
// and dup2 the output to the delemeter 

char	*exec_redi_pipe_output(char *cmd, int i)
{
	char	*name;

	name = NULL;
	if (cmd[i] == '>' && cmd[i + 1] == '>')
	{
		name = redirection_name(ft_strdup(cmd + i + 2));
		cmd = exlude_name(cmd, i, 2);
		redirect_output(name, O_APPEND);
		free(name);
	}
	else if (cmd[i] == '>')
	{
		name = redirection_name(ft_strdup(cmd + i + 1));
		cmd = exlude_name(cmd, i, 2);
		redirect_output(name, O_TRUNC);
		free(name);
	}
	return (name);
}

// it call for the remained heredoc and printf an error and quit

void	fail_exec_redi_pipe_input(char *cmd, int i, char *name)
{
	cmd = exlude_name(cmd, i, 0);
	extande_heredoc(cmd);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(" : no such file or directory\n", 2);
	exit(1);
}
