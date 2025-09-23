/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:27 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:28 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_var(char *str, size_t *i, size_t *len, t_env *env)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(&str[*i]);
	if (var_name)
	{
		var_value = get_env_value(env, var_name);
		if (var_value)
			*len += ft_strlen(var_value);
		free(var_name);
	}
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
}

void	process_var_len(char *str, size_t *i, size_t *len, t_shell *shell)
{
	if (classify_dollar(str[*i + 1]) == ENV_VAR)
		handle_env_var(str, i, len, shell->env);
	else if (classify_dollar(str[*i + 1]) == EXIT_STATUS)
	{
		*len += int_len(shell->last_exit_code);
		*i += 2;
	}
	else if (classify_dollar(str[*i + 1]) == LITERAL)
	{
		(*len)++;
		(*i)++;
	}
	else if (classify_dollar(str[*i + 1]) == INVALID)
		*i += 2;
}

size_t	expanded_len(char *str, t_shell *shell)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
			process_var_len(str, &i, &len, shell);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
