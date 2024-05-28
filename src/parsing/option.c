/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:04:10 by ekrause           #+#    #+#             */
/*   Updated: 2024/05/28 13:05:41 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *get_option(char *prompt)
{
	char *option;
	int len;
	int i;
	int j;

	option = "t";
	len = 0;
	i = 0;
	while (prompt[i] && prompt[i] != ' ')
		i++;
	i++;
	j = i;
	while (prompt[i] && prompt[i] != ' ')
	{
		len++;
		i++;
	}
	option = malloc(sizeof(char) * (len + 1));
	if (!option)
		return (NULL);
	i = 0;
	while (i < len)
		option[i++] = prompt[j++];
	option[i] = '\0';
	return (option);
}

int option_is_valid(char *option)
{
	char *option_list;
	int i;

	option_list = "-n";
	i = 0;
	if (ft_strcmp(option, option_list))
		return (1);
	return (0);
}