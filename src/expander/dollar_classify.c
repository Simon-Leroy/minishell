/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_classify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:17 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 11:44:56 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Fonction pour classer le caractère qui suit le signe dollar

-Si ? --> expansion plus tard sur le exit status
-Si lettre ou underscore --> variable d'environnement valide à tester
-Si commence par un chiffre --> invalide (pas demandé par le sujet de traiter
les cas de $ + chiffre qui renvoient certaines valeurs)
-Sinon --> literal qu'on expand pas (echo $+ va print $+)
*/
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

/*
Extrait le nom de la variable d'environnement

-Si $HOME_TEST123 --> renvoie HOME_TEST123
-Si c'est un literal (à ne pas expand), renvoie juste $
-Sinon renvoie une chaîne vide
*/
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
