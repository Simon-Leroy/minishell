/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:42 by roguille          #+#    #+#             */
/*   Updated: 2025/09/26 16:49:03 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	res;

	res = 0;
	while (args[res])
		res++;
	return (res);
}

/* Remet a jour PWD apres chaque utilisation de cd
==> Parcourt la liste d'environnement, quand on tombe sur PWD,
on reassigne a la cle PWD le repertoire courant avec getcwd */
static void	change_pwd(t_env *env)
{
	char	new_pwd[PATH_MAX];
	t_env	*parse;

	if (!env)
		return ;
	parse = env;
	while (parse)
	{
		if (!ft_strcmp(parse->key, "PWD"))
		{
			if (parse->value)
				free(parse->value);
			getcwd(new_pwd, PATH_MAX);
			parse->value = ft_strdup(new_pwd);
		}
		parse = parse->next;
	}
}

/* Gere le cas ou la fonction cd est utilisee seule sans argument
1)On recupere la valeur de HOME dans l'environnement
2)On va dans ce repertoire avec chdir
3)On modifie pwd avec la fonction change_pwd precedente
4)Renvoie 0 en cas de succes */
static int	cd_alone(t_env *env)
{
	char	*target;
	int		res;

	target = get_env_value(env, "HOME");
	if (!target)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	res = chdir(target);
	change_pwd(env);
	if (res == 0)
		return (0);
	perror(target);
	return (1);
}

/* -Si un seul argument = cd seul
-Si deux arguments, on essaye de se rendre vers le
dossier indique et on change pwd ; si le dossier n'existe pas
renvoie une erreur
-Si plus de deux arguments : erreur */
int	ft_cd(char **args, t_env *env)
{
	int	res;
	int	nbr_args;

	nbr_args = count_args(args);
	if (nbr_args == 1)
		return (cd_alone(env));
	if (nbr_args == 2)
	{
		res = chdir(args[1]);
		change_pwd(env);
		if (res == 0)
			return (0);
		if (res < 0)
		{
			perror(args[1]);
			return (1);
		}
	}
	if (nbr_args > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	return (1);
}
