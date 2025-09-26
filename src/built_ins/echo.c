/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:47 by roguille          #+#    #+#             */
/*   Updated: 2025/09/26 16:26:07 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
echo -n bonjour = print bonjour sans mettre de retour a la ligne

check_option permet de valider l'option associee a echo
- -n ou -nnnnnnn sont valides
- -ne ou abc ne le sont pas */
static int	check_option(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (i == ft_strlen(str))
			return (1);
	}
	return (0);
}

/* 1)Tant qu'il y a des options on avance dans args et on met newline a 0
==> gere plusieurs options comme echo -n -n -nnn bonjour
2)On imprime les caracteres suivants separes par des espaces
3)Si newline vaut il n'y a pas eu d'option on ajoute \n */
static void	print_echo(int count, int i, int newline, char **args)
{
	while (args[i] && check_option(args[i]))
	{
		i++;
		newline = 0;
	}
	while (i < count)
	{
		printf("%s", args[i]);
		if (i != count - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

/* -On compte le nombre d'arguments et on commence a 1
car args[0] = "echo"
-On initialise newline a 1 donc retour a ligne par defaut
sauf si des options sont detectees dans print_echo */
int	ft_echo(char **args)
{
	int		count;
	int		i;
	int		newline;

	count = 0;
	while (args[count])
		count++;
	i = 1;
	newline = 1;
	print_echo(count, i, newline, args);
	return (0);
}
