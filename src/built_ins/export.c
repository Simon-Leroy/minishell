/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:57 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 10:22:50 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checke le nom de la variable utilisee pour export et unset:
-le nom ne peut commencer que par une lettre ou par underscore _
-les caracteres suivants ne peuvent etre qu'alphanumeriques ou underscore
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
Fonction pour isoler la valeur de la variable exportee
donc apres le signe =
export ABC=bonjour --> bonjour
*/
char	*get_export_value(char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
		return (ft_strdup(equal_sign + 1));
	else
		return (ft_strdup(""));
}

/* Fonction pour isoler le nom de la variable exportee
donc avant le signe =
-substr(str, start, len) renvoie la string commencant a start
et de longueur len*/
char	*get_export_key(char *str)
{
	char	*equal_sign;
	size_t	len;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
		len = equal_sign - str;
	else
		len = ft_strlen(str);
	return (ft_substr(str, 0, len));
}

/* Fonction print d'erreur en cas de nom de valeur non valide */
void	print_export_error(char *identifier)
{
	write(2, "export: '", 10);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
}

/* Fonction d'export, plusieurs variables peuvent etre exportees d'un coup

1)Check si le nom de la variable est valide
2)Si valide, on extrait le nom et la valeur et on les met
dans l'environnement avec set_env

On return a la toute fin et pas dans la boucle car il faut pouvoir
checker toutes les variables et print toutes les erreurs */
int	ft_export(char **args, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	int		error;

	error = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_export_error(args[i]);
			error = 1;
		}
		else
		{
			key = get_export_key(args[i]);
			value = get_export_value(args[i]);
			set_env(env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (error);
}
