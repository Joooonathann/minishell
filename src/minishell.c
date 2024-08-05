/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/08/05 16:21:27 by ekrause          ###   ########.fr       */
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
		char *test = get_prompt();
		prompt = readline(test);
		if (!prompt)
		{
			delete_all_vars(&env);
			free(prompt);
			free(test);
			free(cpy_pwd);
			exit(EXIT_SUCCESS);
		}
		if (prompt && *prompt)
		{
			printf ("%s\n", prompt);
			tokens = parser(prompt, &env);
			//handler_command(tokens, &env, &cpy_pwd);
			add_history(prompt);
			ft_free_tokens(&tokens);
		}
		free(prompt);
		free(test);
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_vars *env;
// 	(void)argc;
// 	(void)argv;
// 	int i = 0;
// 	char *tests[] = {
// 		// Test 1: Simple expansion de variable d'environnement
// 		"echo $USER",

// 		// Test 2: Expansion dans une chaîne avec guillemets doubles
// 		"echo \"$HOME/bin\"",

// 		// Test 3: Expansion dans une chaîne avec guillemets simples (ne devrait pas s'étendre)
// 		"echo '$HOME/bin'",

// 		// Test 4: Expansion dans une chaîne mixte de guillemets simples et doubles
// 		"echo \"$HOME/$USER\"",

// 		// Test 5: Variable d'environnement dans guillemets simples, guillemets doubles extérieurs
// 		"echo \"'$HOME'\"",

// 		// Test 6: Variable d'environnement dans guillemets simples, guillemets doubles internes
// 		"echo '$HOME\"$USER\"'",

// 		// Test 7: Expansions imbriquées avec plusieurs variables
// 		"echo \"$USER is at $HOME\"",

// 		// Test 8: Variables d'environnement avec des caractères non alphanumériques
// 		"echo \"Path: $HOME/Documents/file.txt\"",

// 		// Test 9: Variable d'environnement non définie
// 		"echo \"$UNDEFINED_VAR\"",

// 		// Test 10: Mélange de guillemets simples et doubles avec des variables
// 		"echo \"$USER and '$HOME'\"",

// 		// Test 11: Chaîne vide avec guillemets doubles
// 		"echo \"\"",

// 		// Test 12: Chaîne vide avec guillemets simples
// 		"echo ''",

// 		// Test 13: Chaîne avec des guillemets imbriqués
// 		"echo \"hello 'world'\"",

// 		// Test 14: Chaîne avec guillemets imbriqués et variables
// 		"echo \"hello '$USER'\"",

// 		// Test 15: Variables dans des chaînes vides avec des guillemets
// 		"echo \"'$USER'\"",

// 		// Test 16: Variable d'environnement à l'intérieur de guillemets simples et doubles
// 		"echo \"'$USER\"",

// 		// Test 17: Chaîne avec guillemets imbriqués et variables
// 		"echo \"'hello $USER'\"",

// 		// Test 18: Chaîne avec des guillemets et des variables d'environnement
// 		"echo \"'$USER'\"",

// 		// Test 19: Variations de guillemets simples dans la chaîne
// 		"echo 'hello'\"$USER\"",

// 		// Test 20: Chaîne avec guillemets doubles et variables d'environnement
// 		"echo \"$USER\"",

// 		// Test 21: Cas complexe avec guillemets imbriqués et variables d'environnement
// 		"echo \"'$USER \"'\"",

// 		// Test 22: Variable d'environnement concaténée avec d'autres caractères
// 		"echo \"$USER's path is $HOME/path\"",

// 		// Test 23: Chaîne vide avec variable d'environnement non définie
// 		"echo \"$UNDEFINED_VAR\"",

// 		// Test 24: Variations de guillemets imbriqués avec variables
// 		"echo \"$USER\"'world'",

// 		// Terminaison du tableau
// 		NULL};

// 	env = NULL;
// 	init_vars(&env, envp);

// 	while (tests[i])
// 	{
// 		printf("%d %s\n",i ,tests[i]);
// 		parser(tests[i++] ,&env);
// 		printf("\n");
// 	}
// }