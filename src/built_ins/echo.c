/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:47 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:50:49 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
