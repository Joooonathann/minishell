/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:49 by jalbiser          #+#    #+#             */
/*   Updated: 2024/05/30 14:06:39 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

char	*get_prompt(void)
{
	char	*result;
	char	*username;
	char	hostname[HOST_NAME_MAX + 1];
	char	cwd[PATH_MAX];

	username = getenv("USER");
	if (!username)
		username = "minishell";
	if (gethostname(hostname, sizeof(hostname)) != 0)
		ft_strcpy(hostname, "42");
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strcpy(cwd, "ERROR");
	size_t prompt_len = ft_strlen(username) + ft_strlen(hostname) + ft_strlen(cwd) + 5;
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
	if (signal == SIGQUIT)
		exit(1);
}

int	main(void)
{
	char *prompt;

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
			parsing(prompt);
			add_history(prompt);
		}
		free(prompt);
	}
}