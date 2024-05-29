/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/29 10:49:25 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// int ft_strcmp(char *s1, char *s2)
// {
// 	int i;

// 	if (!s1 || !s2)
// 		return (0);
// 	if (ft_strlen(s1) != ft_strlen(s2))
// 		return (0);
// 	i = 0;
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void parsing(char *prompt)
{
	char	**tokens;

	tokens = ft_split(prompt, ' ');
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}
