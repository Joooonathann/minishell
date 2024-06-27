/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:58:52 by ekrause           #+#    #+#             */
/*   Updated: 2024/06/27 17:09:30 by ekrause          ###   ########.fr       */
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
