/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:59:05 by hchahid           #+#    #+#             */
/*   Updated: 2022/12/20 22:50:41 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_env **env, char **envp)
{
	modify_attr();
	set_env_vars(envp, env);
	sig_init();
}

int	syntax(char *buf)
{
	if (buf[0] == '\0')
		return (1);
	if (check_qotes(buf) == 0)
		return (1);
	if (redirection_syntax(buf) == 1)
		return (printf("redirection error\n"));
	if (pipe_syntax(buf) == 1)
		return (printf("pipe error\n"));
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_env				*env_p;
	char				*buf;

	(void)ac;
	(void)av;
	env_p = NULL;
	buf = NULL;
	init(&env_p, envp);
	while (1)
	{
		buf = readline ("\033[0;34m(minishell) : \033[0;37m");
		if (!buf)
		{
			release_e_var(&env_p);
			exit(0);
		}
		else if (*buf)
			add_history(buf);
		if (syntax(buf))
		{
			free(buf);
			continue ;
		}
		execute(buf, &env_p);
	}
}
