/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchahid <hchahid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:07 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/20 10:31:57 by hchahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# include <errno.h>

// #define RED \033[0;31m
// #define GREEN \033[0;32m
// #define YELLOW \033[0;33m
// #define BLUE \033[0;34m
// #define PURPLE \033[0;35m
// #define WHITE \033[0;37m

typedef struct s_redi
{
	char	*name;
	int		next_heredoc;
	int		input1;
	int		pid;
	int		i;
}	t_redi;

typedef struct s_expnd
{
	int		index;
	int		i;
	char	*tmp;
}	t_expnd;

typedef struct s_hold
{
	int		index;
	int		i;
	t_env	**env;
}	t_hold;

t_arg	*get_args(char *s, t_env **env);
char	*join_list(t_arg *cmd);
void	executables(char *buf, t_env **env_p);
int		istherepipe(char *s);
int		execute_pipe(char *buf, t_env **env_p);
int		skip_space(char *buf, int i);
int		after_star(t_star s);
int		execute(char *buf, t_env **env_p);
void	execute2(char *buf, t_env **env_p);
char	**list_to_tab(t_env *env);
t_arg	*last_arg(t_arg *lst);
char	**remove_qoutes_splited(char	**buf);
int		execute_redirection(char *buf, t_env **env_p, char *file);
int		is_redirection(char c);
void	cmd(t_arg *arg, t_env **env);
char	**prepar_tb_cmd(t_arg *arg);
void	no_path(char **splited);
int		execute_redirection_pipe(char *buf,
			t_env **env_p, char *file, t_arg *arg);
void	delete_arg(t_arg *p);
void	binary_file(char **splited, t_env **env);
void	check_for_binaries(char **splited, t_env **env);
int		wildcardcheck(t_arg *r, t_arg *node);
char	*empty_out(char *name);
char	*set_up_name(char *buf, char *special_string);
char	*new_name(char *name, int len);
int		end_of_name(char *s);
int		end_of_arg(char *s);
int		quoted_redirection(char *s, int i);
int		add_back_arg(t_arg **lst, t_arg *new);
char	*new_arg_sq(char *arg);
char	*new_arg_dq(char *arg, t_env **env_p, t_star s, t_arg *r);
t_arg	*new_arg(t_env **env_p, t_arg *r, t_star s, char linked);
int		get_normal_arg(char *buf, t_hold *c, t_star star, t_arg **r);
int		get_heredoc_arg(char *buf, t_hold *c, t_star star, t_arg **r);
t_arg	*remove_qoutess(t_arg *comand);
char	*full_replace_env(char *buf, t_env **env);
char	*replace_env(char *buf, t_env **env);
char	*replace_wild_card(char *buf, t_expnd c, char *wild);
char	*replace_var(char *buf, t_expnd c, t_env **env);
t_expnd	ds(int i, int index, char *tmp);
int		is_there_exitstat_check(char *buf, int i);
int		cut_false_env(char **buf, int i, int index);
int		replace_exit_status(char **buf, int i);
int		outputcheck(char *s, int hd);
int		first_heredoc(char *s, int hd);
char	*redirection_name(char *buf);
char	*exclude_name1(char *str, int start, int i, char *new);
char	*exlude_name(char	*str, int start, int end);
int		redirect_output(char *name, unsigned int open_flag);
char	*exec_redi_pipe_input(char *cmd, int i);
void	fake_herdoc(char	*delemeter);
void	herdoc(char	*delemeter, int fd);
void	extande_heredoc(char *buf);
char	*get_redi(t_arg *command);
int		files_count(void);
int		redirection_count(char *s);
int		first_redirection(char *s);
int		isthereredirection(t_arg *s);
int		is_quoted(char *s, char *mark);
char	*ft_strdup(const char *s1);
char	*replace_exstat_val(char *buf, int start, int finish);
char	*expand_it(char *buf, t_expnd c, t_env **env_p);
int		is_empty(char	*str);
int		env_exist(t_env **env_p, char *name);
char	*remove_arg(char *buf, int start, int end);
char	*sub_str(char *s, int start, int end);

void	redirection(t_arg *command, char *buf, t_env **env_p);
char	*exec_redirection_pipe(t_arg *command, char **buf,
			t_env **env_p, int *pipe_redi);
char	*exec_redi_loop_pip(char *cmd);
char	*exec_redi_pipe_herdoc(char *cmd, int i);
void	exec_redi_pipe_herdoc2(char	*name);
void	fail_exec_redi_pipe_input(char *cmd, int i, char *name);
char	*exec_redi_pipe_output(char *cmd, int i);
char	*get_file_names(void);
char	*get_right_file_names(char	**files, char *name);
char	**get_dir_files(int i);
int		quoted_heredoc(char *s, int i);
int		closing_quote(char *line, char quote, int i);
int		still_in_name(char c);
char	*get_less_pwd_evar(t_env *p);
int		count_backing(char *dir);
void	join_err_pwd(char*dir);
void	get_pre_dir(void);
char	*get_pwd_evar(t_env *p);
char	**cmd_arg(char *buf);
char	**get_cmd_arg_size(char *buf);
void	err_malloc_msg(void);
char	*get_e_var_value(char *value);
void	update_pwd_env(t_env **env_p, char *old_pwd, char *new_pwd);
void	release_e_var(t_env **env_p);
size_t	ft_strlen(const char *s);
void	fill_t_fd(t_fd *fd_pipe, int in, int out, int rest);
char	**joincmd(t_arg *arg);
void	sig_init(void);
void	sig_default(void);
void	current_directory_error(char *old_pwd, char *new_pwd,
			char **splited, t_env **env_p);
void	previous_directory_error(char *old_pwd, char *new_pwd,
			char **splited, t_env **env_p);
void	valid_cd(char *new_pwd, char *old_pwd, char *dir, t_env **env_p);
int		directory_err_cases(char *pwd, char *dir);
void	false_dir(char *old_pwd, char *new_pwd, char **splited, t_env **env_p);

void	ffree(char **s);
char	*join_list(t_arg *cmd);
char	*eraseqout(char *buf, int len);
int		markqout(char	*buf);
// t_arg *get_args(char *s);
char	*full_replace_env(char *buf, t_env **env);
char	*exec_redirection_pipe(t_arg *command, char **buf,
			t_env **env_p, int *pip_redi);
int		execute_redirection_pipe(char *buf, t_env **env_p,
			char *file, t_arg *arg);
t_arg	*get_args(char *s, t_env **env);
void	delete_arg(t_arg *p);
char	*wildcard(void);
int		quoted_space(char *s, int i);
char	*expander(char *buf, t_env **env);
int		env_exist(t_env **env_p, char *name);
char	*empty_string(char *buf);
int		heredoc_name(char *buf, char *mark);
int		last_red_in(char *or, char	*str);
int		is_there_file(char *s);
int		first_input(char *s);
int		ignore_alpha(char *str, int dj);
int		are_qouted(char *str, char	*target);
int		check_qotes(char *str);

int		outputcheck(char *s, int hd);

int		redirection_syntax(char *buf);
int		pipe_syntax(char *buf);
char	*exlude_name(char	*str, int start, int end);
t_arg	*remove_qoutes(t_arg	*command);
int		is_empty(char	*str);
char	*expand_it(char *buf, t_expnd c, t_env **env_p);
void	remove_path(void);
char	*remove_arg(char *buf, int start, int end);

/*-----------------------signals-----------------------*/
void	sighandle(int sig);
void	siginit(void);
void	sigdefault(void);

/*-----------------------enviroment_variables---------------*/
void	set_env_vars(char **envp, t_env **env_p);
void	display(t_env *p);
char	*get_vars(char *s);
void	release_e_var(t_env **env_p);
/*-----------------------built_ins-----------------------*/
int		built_in(char *buf, t_env **env_p, t_arg *arg);
// int		built_in(char *buf, t_env **env_p);
/*-----------------------cd-----------------------*/
int		cd(char **splited, t_env **env_p);

int		e_acces(char *s, char *new_pwd, char *old_pwd, t_env **env_p);
int		cd_home(t_env **env_p, char *old_pwd, char *new_pwd);

int		pwd(t_env *env_p);
int		env(t_env *env_p, char *splited);
int		export(t_env **env_p, char **splited);
int		unset(t_env **env_p, char **splited);
int		fecho(char **s, t_arg *arg);
int		echo(char **splited, t_env **env_p, t_arg *arg);

// int		echo(char **splited, t_env **env_p);
/***********************************************************/

/*-----------------------parsing-----------------------*/

int		syntax_error(char *s);

/***********************************************************/

char	*get_file_names(void);
void	write_e_var(t_env **env_p, char *my_var);

void	release_e_var(t_env **env_p);

void	redirection(t_arg *command, char *buf, t_env **env_p);

int		execute(char *buf, t_env **env_p);

// int	append_from_output(char **splited, t_env **env_p);

void	modify_attr(void);
int		if_directory(char	*buf);

int		is_quoted(char *s, char *mark);

int		isthereredirection(t_arg *s);
char	*join_list(t_arg *cmd);

int		execute_redirection(char *buf, t_env **env_p, char *file);
int		execute_pipe(char *buf, t_env **env_p);

void	mid_end_arg(t_arg **env_p, t_arg *var);
void	del_arg(t_arg **env_p, t_arg *var);
int		pwd_lenght(t_env **env_p);
void	update_pwd_env(t_env **env_p, char *old_pwd, char *new_pwd);
void	update_pwd_vars(char **env_value, char *new_value);
int		redirect_output(char *name, unsigned int open_flag);
char	**redirection_split(char *s);
char	*redirection_name(char *buf);
int		first_redirection(char *s);
int		first_heredoc(char *s, int hd);

int		does_env_exist(t_env **env_p, char *env_var);
void	change_env_value(t_env *env, char *value);

int		redirect_input(char *name);

char	*extract_evar_value(t_env *env, char *name);
int		arg_len(char **s);

void	display_with_declare(t_env *p);
int		is_space(char c);
char	*get_pwd_evar(t_env *p);
char	*get_less_pwd_evar(t_env *p);
int		ft_strcmp(const char *s1, const char *s2);
char	*replace_env(char *buf, t_env **env);

int		rl_replace_line(char *s, int d);

void	join_pwd(t_env **env, char *dir);
void	get_pre_dir(void);
void	join_err_pwd(char *dir);
int		try_dir(char *dir);

char	*join_free(char const *s1, char const *s2);

void	retrieving_err(void);

int		count_backing(char *dir);

void	cut_pre_dir(char **dir);

int		is_quoted(char *s, char *mark);
char	**custom_split(char *s, char c);

/*--------------------pipe_utils------------------*/
void	free_dp(char **s);
void	free_fd(int **fd, char **ag);
int		do_pipe(char *p, t_env **env_p);
int		**prepare_pipe(char **cmd);

#endif
