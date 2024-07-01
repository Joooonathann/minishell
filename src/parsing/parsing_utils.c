/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:58:52 by ekrause           #+#    #+#             */
/*   Updated: 2024/07/01 16:31:00 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	calc_string_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] && str[i++] != '$')
		len++;
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	while (str[i++])
		len++;
	return (len);
}

void	copy_string_and_var(char **result, char *str, char *var)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	y = 0;
	while (str[i] && str[i] != '$')
		(*result)[j++] = str[i++];
	i++;
	while (var && var[y])
		(*result)[j++] = var[y++];
	while (str[i] && is_valid_var_char(str[i]))
		i++;
	while (str[i])
		(*result)[j++] = str[i++];
	(*result)[j] = '\0';
}
