/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/28 16:25:48 by jalbiser         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *prompt;
	t_vars *env;
	t_tokens *tokens;
	(void)envp;
	char	*cpy_pwd;
	
	env = NULL;
	init_vars(&env, envp);
	cpy_pwd = get_vars(&env, "PWD");
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	using_history();
	while (1)
	{
		//prompt = readline("▶ \033[1;32mmyfuckingbash\033[0m@\033[1;34m42\033[0m$ ");
		prompt = readline("Test$ ");
		if (!prompt)
		{
			delete_all_vars(&env);
			free(prompt);
			free(cpy_pwd);
			exit(EXIT_SUCCESS);
		}
		if (prompt && *prompt)
		{
			tokens = parser(prompt, &env);
			if (tokens)
				handler_command(tokens, &env, &cpy_pwd);
			add_history(prompt);
			ft_free_tokens(&tokens);
		}
		free(prompt);
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_vars *env;
// 	(void)argc;
// 	(void)argv;

// 	env = NULL;
// 	init_vars(&env, envp);
// 	parser("| coucou" ,&env);
// }