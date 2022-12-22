/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:27:26 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:31:57 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_redi_pipe_input(char *cmd, int i)
{
	int		input1;
	int		next_heredoc;
	char	*name;

	name = redirection_name(ft_strdup(cmd + i + 1));
	next_heredoc = last_red_in(cmd, cmd + i);
	if (open(name, O_RDONLY) == -1)
		fail_exec_redi_pipe_input(cmd, i, name);
	else
		cmd = exlude_name(cmd, i, 2);
	if (!next_heredoc)
	{
		input1 = open(name, O_RDONLY, 0664);
		if (input1 < 0)
			;
		else if (dup2(input1, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("failed to dup2 \n", 2);
			exit(0);
		}
		close(input1);
	}
	free(name);
	return (cmd);
}

int	redirect_output(char *name, unsigned int open_flag)
{
	int	file;

	file = open (name, O_RDWR | O_CREAT | open_flag, 0664);
	if (file == -1)
		exit (printf("Issue opening file1\n"));
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		exit (printf("Issue opening file2\n"));
	}
	close(file);
	return (0);
}
