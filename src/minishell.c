/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/01 17:24:18 by ekrause          ###   ########.fr       */
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

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	char *prompt;
// 	t_vars *env;
// 	t_tokens *tokens;
// 	(void)envp;
// 	char	*cpy_pwd;
	
// 	env = NULL;
// 	init_vars(&env, envp);
// 	cpy_pwd = get_vars(&env, "PWD");
// 	signal(SIGINT, handler);
// 	signal(SIGQUIT, handler);
// 	using_history();
// 	while (1)
// 	{
// 		char *test = get_prompt();
// 		prompt = readline(test);
// 		if (!prompt)
// 		{
// 			delete_all_vars(&env);
// 			free(prompt);
// 			free(test);
// 			free(cpy_pwd);
// 			exit(EXIT_SUCCESS);
// 		}
// 		if (prompt && *prompt)
// 		{
// 			printf ("%s\n", prompt);
// 			tokens = parser(prompt, &env);
// 			handler_command(tokens, &env, &cpy_pwd);
// 			add_history(prompt);
// 			ft_free_tokens(&tokens);
// 		}
// 		free(prompt);
// 		free(test);
// 	}
// }

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	int i = 0;
	char *tests[] = {
		"echo coucou",
		"echo \"coucou\"",
		"echo 'coucou'",
		"echo coucou > file.txt",
		"echo \"coucou\" > file.txt",
		"echo 'coucou' > file.txt",
		"echo coucou >> file.txt",
		"echo coucou | grep coucou",
		"echo coucou | grep coucou > file.txt",
		"echo coucou | grep \"coucou\" > file.txt",
		"echo 'coucou' | grep 'coucou'",
		"echo 'coucou' > file.txt | grep 'coucou'",
		"echo \"\" > file.txt",
		"echo \"coucou\" \"coucou\"",
		"echo 'coucou' \"coucou\"",
		"echo \"coucou 'hello'\" \"world\"",
		"echo \"coucou 'hello world'\"",
		"echo \"coucou\\\"",
		"echo \"coucou\\\\\"",
		"echo 'coucou\\' \"world\"",
		"echo 'coucou\"world'",
		"echo 'coucou\\\\' world",
		"echo 'coucou>file' > file.txt",
		"echo \"coucou > file\" > file.txt",
		"echo \"coucou'world\" > file.txt",
		"echo 'coucou\"world' > file.txt",
		"echo \"coucou > file > more\" > file.txt",
		"echo 'coucou | grep' > file.txt",
		"echo \"coucou 'with spaces'\" | grep \"pattern\" > file.txt",
		"echo \"coucou\"|grep 'pattern'|awk '{print $1}'",
		"echo 'coucou'\"'world\" > file.txt",
		"echo \"coucou 'mixed quotes\" > file.txt",
		"echo \"coucou' world\" > file.txt",
		NULL
	};

	while (tests[i])
	{
		printf("%d %s\n",i ,tests[i]);
		parser(tests[i++] ,NULL);
		printf("\n");
	}
}