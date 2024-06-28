/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_value_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalbiser <jalbiser@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:19:40 by jalbiser          #+#    #+#             */
/*   Updated: 2024/06/28 18:32:26 by jalbiser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_value_tokens(t_tokens *tokens)
{
    int i;

    if (!tokens)
        return (0);
    i = 0;
    while (tokens)
    {
        while (tokens->value[i])
            i++;
        tokens = tokens->next;
    }
    return (i);
}