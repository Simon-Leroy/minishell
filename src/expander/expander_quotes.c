/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:20 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:21 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(char *str, int *d_quote, int *s_quote, int *i)
{
	if (str[*i] == '\'' && !*d_quote)
	{
		*s_quote = !*s_quote;
		(*i)++;
	}
	else if (str[*i] == '"' && !*s_quote)
	{
		*d_quote = !*d_quote;
		(*i)++;
	}
}

size_t	len_without_quotes(char *str)
{
	size_t	len;
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	len = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		handle_quotes(str, &in_double, &in_single, &i);
		if (str[i] && !((str[i] == '\'' && !in_double)
				|| (str[i] == '"' && !in_single)))
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		k;
	int		in_single;
	int		in_double;

	new_str = malloc(len_without_quotes(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		handle_quotes(str, &in_double, &in_single, &i);
		if (str[i] && !((str[i] == '\'' && !in_double)
				|| (str[i] == '"' && !in_single)))
			new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	return (new_str);
}
