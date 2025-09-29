/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:19 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 12:17:11 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Alloue la mémoire pour la chaîne de caractères une fois expand */
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

/*
Fonction qui gère le suivi des quotes, le déclenchement
de l'expansion et la copie des caractères normaux

-Si on rencontre un single quote, et qu'on n'est pas dans des double
quotes, on inverse l'état des single quotes, 0 -> fermé, 1 -> ouvert
On copie le single quote et on avance les pointeurs

-Si on rencontre un double quote, pareil en inversé

-Si on est pas dans des quotes simples et qu'on tombe sur un dollar,
on appelle process_env_var_copy qui va extraire et copier la valeur de
la variable d'environnement

-Sinon on copie simplement le caractère

Pour réduire le nombre de paramètres dans la fonction :
	quotes[0] --> quand on est dans une single quote
	quotes[1] --> quand on est dans une double quote

Utilisation des doubles pointeurs pour moins de paramètres.
Equivalent à cursor[(*i)++] = src[(*j)++]
*/

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

/*
Fonction finale pour retourner la chaîne expanded

On fait pointer cursor sur le début de la chaîne exp puis
on se sert de cursor pour remplir la chaîne dans la fonction
handle_expansion_char.
A la fin on renvoie exp qui pointe toujours sur le début de la chaîne
qui a été remplie avec les bons caractères
*/
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
