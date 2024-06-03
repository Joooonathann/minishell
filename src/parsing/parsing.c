/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:52:19 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/03 18:03:45 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define quote unsigned int
#define simple 39
#define double 34

//////// en construction ////////

// void	token_do(char	*token)
// {
// 	t_tokens	*token_list;
// 	t_tokens	*token_node;

// 	token_list = NULL;
// 	token_node = ft_tokennew(ft_strdup(token), 1);
// 	ft_tokenadd_back(&token_list, token_node);
// 	printf("%s\n", token_node->value);
// }

// void	tokenize(char *string)
// {
// 	char	token[255];
// 	int		i;
// 	int		j;
// 	bool	in_quote;

// 	i = 0;
// 	j = 0;
// 	in_quote = false;
// 	while (string[i])
// 	{
// 		if (string[i] == '"' && in_quote == false)
// 			in_quote = true;
// 		else if (string[i] == '"' && in_quote == true)
// 		{
// 			in_quote = false;
// 			token[j] = '\0';
// 			j = 0;
// 			token_do(token);
// 		}
// 		else if (string[i] == ' ' && in_quote == false)
// 		{
// 			token[j] = '\0';
// 			j = 0;
// 			token_do(token);
// 		}
// 		else
// 			token[j++] = string[i];
// 		i++;	
// 	}
// 	if (j > 0)
// 	{
// 		token[j] = '\0';
// 		token_do(token);
// 	}
// }

int	count_double_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == double)
			j++;
		i++;
	}
	return (j);
}

int count_simple_quote(char *str)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == simple)
			j++;
		i++;
	}
	return (j);
}

void	tokenizer(char *str)
{
	char	token[255];
	int 	i;
	int		j;
	int		double_quote;
	int		simple_quote;
	
	bool	in_quote;
	quote	quote_type;
	i = 0;
	j = 0;
	double_quote = count_double_quote(str);
	simple_quote = count_simple_quote(str);
	printf("%d\n%d\n", double_quote, simple_quote);
	in_quote = false;
	while (str[i])
	{
		if ((str[i] == simple && !in_quote && simple_quote > 1)
		|| (str[i] == double && !in_quote && double_quote > 1))
		{
			if (str[i] == simple)
				quote_type = simple;
			else if (str[i] == double)
				quote_type = double;
			in_quote = true;
		}
		else if ((str[i] == simple && quote_type == simple && in_quote) ||
		(str[i] == double && quote_type == double && in_quote))
		{
			in_quote = false;
			token[j] = '\0';
			j = 0;
			printf("Token: %s\n", token);
		}
		else if (str[i] == ' ' && !in_quote)
		{
			token[j] = '\0';
			j = 0;
			printf("Token: %s\n", token);
		}
		else
			token[j++] = str[i];
		i++;
	}
	if (j > 0)
	{
		token[j] = '\0';
		printf("Token: %s\n", token);
	}
}

void	parser(char *string)
{
	// t_tokens	*tokens;
	// char		*token;
	// char		**tab;
	// int i;
	tokenizer(string);

	// tokens = NULL;
	// tab = ft_split(line, ' ');
	// if (!tab)
	// 	return ;
	// i = 0;
	// while (tab[i])
	// {
	// 	token = ft_strdup(tab[i]);
	// 	if (!token)
	// 	{
	// 		free_tab(&tab);
	// 		return;
	// 	}
	// 	ft_tokenadd_back(&tokens, ft_tokennew(token, i));
	// 	i++;
	// }
	// free_tab(&tab);
	// ft_print_tokens(tokens);
	// ft_free_tokens(&tokens);
}
