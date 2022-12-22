/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 05:23:16 by abelahce          #+#    #+#             */
/*   Updated: 2022/12/20 05:25:58 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redi_pipe_herdoc2(char	*name)
{
	int		input1;
	char	*file;

	file = get_file_names();
	input1 = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	herdoc(name, input1);
	close(input1);
	input1 = open(file, O_CREAT | O_RDWR, 0664);
	if (dup2(input1, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("failed to dup2 \n", 2);
		exit(0);
	}
	close(input1);
	free(file);
}

// it excludes the heredoc and its delemeter from the command
// check if its the last redi-in and prok heredoc and dup it to STDOUT
// ^^ call exec_redi_pipe_herdoc2
// if not the last heredoc it call for a fake heredoc

char	*exec_redi_pipe_herdoc(char *cmd, int i)
{
	char	*name;
	int		next_heredoc;

	name = redirection_name(ft_strdup(cmd + i + 2));
	next_heredoc = last_red_in(cmd, cmd + i);
	cmd = exlude_name(cmd, i, 2);
	if (next_heredoc)
		fake_herdoc(name);
	else if (!next_heredoc)
		exec_redi_pipe_herdoc2(name);
	free(name);
	return (cmd);
}

char	*exec_redi_loop_pip(char *cmd)
{
	int	i;

	i = 0;
	if (first_heredoc(cmd, 2) != -1)
		i = first_heredoc(cmd, 2);
	else
		i = first_redirection(cmd);
	if ((cmd[i] == '>' && cmd[i + 1] == '>') || cmd[i] == '>')
		cmd = exec_redi_pipe_output(cmd, i);
	if (cmd[i] == '<' && cmd[i + 1] == '<')
		cmd = exec_redi_pipe_herdoc(cmd, i);
	else if (cmd[i] == '<')
		cmd = exec_redi_pipe_input(cmd, i);
	return (cmd);
}
// while still a rediraction in the command it call for exec_redi_loop_pip
// to work on every redirection 

char	*exec_redirection_pipe(t_arg *command, char **buf,
			t_env **env_p, int *pipe_redi)
{
	char	*cmd;
	char	*file;

	(void)env_p;
	(void)pipe_redi;
	cmd = *buf;
	file = get_file_names();
	cmd = get_redi(command);
	while (first_redirection(cmd) != -1)
		cmd = exec_redi_loop_pip(cmd);
	cmd = join_list(command);
	free(*buf);
	*buf = cmd;
	return (file);
}

void	redirection(t_arg *command, char *buf, t_env **env_p)
{
	char	*file;
	int		pid;

	file = get_file_names();
	pid = fork();
	if (pid == -1)
	{
		printf("\033[0;31mUnable to create processe\n");
		return ;
	}
	else if (pid == 0)
	{
		buf = get_redi(command);
		while (first_redirection(buf) != -1)
			buf = exec_redi_loop_pip(buf);
		buf = join_list(command);
		execute_redirection(buf, env_p, file);
		exit(0);
	}
	sig_init();
	waitpid(pid, &(g_var.exit_status), 0);
	free(file);
	delete_arg(command);
	check_exit_status(pid);
}
