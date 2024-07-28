/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/07/28 17:46:37 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*result;
	char	*username;
	char	hostname[HOST_NAME_MAX + 1];
	char	cwd[PATH_MAX];
	size_t	prompt_len;

	username = getenv("USER");
	if (!username)
		username = "minishell";
	if (gethostname(hostname, sizeof(hostname)) != 0)
		ft_strcpy(hostname, "42");
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strcpy(cwd, "ERROR");
	prompt_len = ft_strlen(username) + ft_strlen(hostname) + ft_strlen(cwd) + 5;
	result = (char *)malloc(prompt_len + 1);
	result[0] = '\0';
	ft_strcat(result, username);
	ft_strcat(result, "@");
	ft_strcat(result, hostname);
	ft_strcat(result, ":");
	ft_strcat(result, cwd);
	ft_strcat(result, "$ ");
	return (result);
}

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
	cpy_pwd = ft_strdup(get_vars(&env, "PWD"));
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	using_history();
	while (1)
	{
		prompt = readline(get_prompt());
		if (!prompt)
			exit(EXIT_SUCCESS);
		if (prompt && *prompt)
		{
			printf ("%s\n", prompt);
			tokens = parser(prompt, &env);
			handler_command(tokens, &env, &cpy_pwd);
			add_history(prompt);
			ft_free_tokens(&tokens);
		}
		free(prompt);
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
	
// 	t_tokens *tokens;
// 	tokens = parser("echo coucou \"\"", NULL);
// 	// char *strings[] = { "command argument",
// 	// 					"echo 'hello world'",
// 	// 					"echo \" hello world \"",
// 	// 					"ls -l > output.txt",
// 	// 					"echo 'hello \"world\"' | grep \"hello world\"",
// 	// 					" command argument ",
// 	// 					"",
// 	// 					"echo $@",
// 	// 					"'command'",
// 	// 					"> output.txt",
// 	// 					"command >",
// 	// 					"command1 arg1 arg2 argv3 argv3 argv3 argv3 argv3 command2 arg1 arg2 argv3 argv3 argv3 argv3 argv3 argv3 argv3 argv3 argv3 ",
// 	// 					"echo>>oui | non <<jesais pas et toi \"comment tu vas\">>non||il y a 'deux pipes ici'",
// 	// 					"echo $+",
// 	// 					NULL};
// 	// int i = 0;
// 	// while (strings[i])
// 	// {
// 	// 	tokens = parser(strings[i], NULL);
// 	// 	ft_free_tokens(&tokens);
// 	// 	i++;
// 	// }
// }
