/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:58 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 18:34:04 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*cwd;
	char	dir[PATH_MAX];

	cwd = getcwd(dir, PATH_MAX);
	if (cwd)
	{
		printf("%s\n", dir);
		return (0);
	}
	cwd = getenv("PWD");
	if (cwd)
	{
		printf("%s\n", cwd);
		return (0);
	}
	printf("/unknown directory\n");
	return (0);
}
