/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:58 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:50:59 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	dir[PATH_MAX];

	if (getcwd(dir, PATH_MAX))
	{
		printf("%s\n", dir);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
