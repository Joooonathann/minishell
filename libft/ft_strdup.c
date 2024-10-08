/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:34:44 by ekrause           #+#    #+#             */
/*   Updated: 2024/08/05 16:34:34 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2)
		ft_strlcpy(s2, s1, len + 1);
	return (s2);
}
