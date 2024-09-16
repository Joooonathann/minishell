/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/16 16:08:21 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	cleanup_and_exit(t_vars **env, char *prompt, char *cpy_pwd)
{
	delete_all_vars(env);
	free(prompt);
	free(cpy_pwd);
	exit(EXIT_SUCCESS);
}

static void	process_prompt(t_vars **env, char *prompt, char **cpy_pwd)
{
	t_tokens	*tokens;

	if (prompt && *prompt)
	{
		tokens = parser(prompt, env);
		if (tokens)
		{
			handler_command(tokens, env, cpy_pwd);
			ft_free_tokens(&tokens);
		}
		add_history(prompt);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_vars	*env;
	char	*cpy_pwd;

	(void)argc;
	(void)argv;
	env = NULL;
	init_vars(&env, envp);
	cpy_pwd = get_vars(&env, "PWD");
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	using_history();
	while (1)
	{
		prompt = readline("myfuckingbash@42$ ");
		if (!prompt)
			cleanup_and_exit(&env, prompt, cpy_pwd);
		process_prompt(&env, prompt, &cpy_pwd);
		free(prompt);
	}
}
