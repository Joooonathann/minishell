/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/09/11 17:59:54 by jalbiser         ###   ########.fr       */
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
	char	*cpy_pwd;
	
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
			{
				//handler_command(tokens, &env, &cpy_pwd);
				ft_free_tokens(&tokens);
			}
			add_history(prompt);
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