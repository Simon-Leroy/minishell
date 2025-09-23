/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:19 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:20 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*alloc_expanded_str(char *str, t_shell *shell)
{
	size_t	len;
	char	*exp;

	len = expanded_len(str, shell);
	exp = malloc(sizeof(char) * (len + 1));
	if (!exp)
		return (NULL);
	return (exp);
}

/* Pour réduire le nombre de paramètres dans la fonction :
	quotes[0] --> quand on est dans une single quote
	quotes[1] --> quand on est dans une double quote */

static void	handle_expansion_char(char **src, char **cursor,
		int quotes[2], t_shell *shell)
{
	if (**src == '\'' && quotes[1] == 0)
	{
		quotes[0] = !quotes[0];
		*(*cursor)++ = *(*src)++;
	}
	else if (**src == '"' && quotes[0] == 0)
	{
		quotes[1] = !quotes[1];
		*(*cursor)++ = *(*src)++;
	}
	else if (quotes[0] == 0 && **src == '$')
		process_env_var_copy(src, cursor, shell);
	else
		*(*cursor)++ = *(*src)++;
}

char	*expand_str(char *str, t_shell *shell)
{
	char	*exp;
	char	*cursor;
	char	*src;
	int		quotes[2];

	exp = alloc_expanded_str(str, shell);
	if (!exp)
		return (NULL);
	cursor = exp;
	src = str;
	quotes[0] = 0;
	quotes[1] = 0;
	while (*src)
		handle_expansion_char(&src, &cursor, quotes, shell);
	*cursor = '\0';
	return (exp);
}

/* int main()
{
	t_shell	shell;

	shell.last_exit_code = 127;
	char *str = "bonjour $USER$USER $?abcdef $9HOME";
	char *expand = expand_str(str, &shell);

	printf("%li\n", expanded_len(str, &shell));
	printf("%li\n", ft_strlen(expand));
	printf("%s\n", expand);
	free(expand);
} */
