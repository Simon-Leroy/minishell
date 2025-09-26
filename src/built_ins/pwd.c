/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:58 by roguille          #+#    #+#             */
/*   Updated: 2025/09/26 15:53:50 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Donne le chemin d'acces ou se situe le user

-getcwd --> donne le chemin d'acces courant
-si getcwd echoue pour repertoire supprime ou autre, on recupere
pwd dans l'env
-si meme pwd n'existe pas on print unknown directory */
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
	printf(" unknown directory\n");
	return (0);
}
