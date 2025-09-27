/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:55 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 10:22:34 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Compte le nombre d'arguments dans la fonction exit */
static int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/*
Determine si la chaine de caractere est numerique ou non
i.e. au format +123 ou -123 ou 123
*/
int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
-Si exit sans argument --> exit avec le dernier code de sortie
-Si plus d'un argument (exit 12 23) --> erreur
-Si bien un seul argument, on enleve les quotes (exit "12" est valide),
si c'est bien un argument numerique on exit avec unsigned char
pour toujours etre entre 0 et 255
*/
int	ft_exit(char **args, int last_status)
{
	int		args_nbr;
	int		code;
	char	*first_arg;

	args_nbr = args_count(args);
	if (!args[1])
		exit(last_status);
	if (args_nbr >= 3)
	{
		write_error("exit", "too many arguments");
		return (1);
	}
	first_arg = remove_quotes(args[1]);
	if (first_arg && !is_numeric(first_arg))
	{
		write_error("exit", "numeric argument required");
		exit(2);
	}
	code = ft_atoi(first_arg);
	free(first_arg);
	exit((unsigned char)code);
}
