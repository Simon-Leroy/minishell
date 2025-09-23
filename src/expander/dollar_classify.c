/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_classify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:17 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:18 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var_type	classify_dollar(char c)
{
	if (c == '?')
		return (EXIT_STATUS);
	else if (ft_isalpha(c) || c == '_')
		return (ENV_VAR);
	else if (ft_isdigit(c))
		return (INVALID);
	else
		return (LITERAL);
}

char	*extract_var_name(char *str)
{
	char			*s;
	t_env_var_type	type;
	size_t			i;

	s = ft_strchr(str, '$');
	if (!s)
		return (NULL);
	s++;
	type = classify_dollar(s[0]);
	i = 0;
	if (type == ENV_VAR)
	{
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
		return (ft_substr(s, 0, i));
	}
	if (type == LITERAL)
		return (ft_strdup("$"));
	return (ft_strdup(""));
}
