/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:00 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 10:23:34 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free une variable d'environnement */
void	free_env_var(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

/*
Supprimer une variable d'environnement, deux cas:
1)la variable est premiere est dans la liste chainée, il faut juste
changer la tete de liste
2)la variable est plus loin, il faut checker toute la liste
et retirer le bon node
*/
int	remove_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*to_free;

	if (!env || !*env)
		return (0);
	if (ft_strcmp((*env)->key, key) == 0)
	{
		to_free = *env;
		*env = (*env)->next;
		free_env_var(to_free);
		return (0);
	}
	current = *env;
	while (current->next)
	{
		if (ft_strcmp(current->next->key, key) == 0)
		{
			to_free = current->next;
			current->next = current->next->next;
			free_env_var(to_free);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

/* Fonction unset, on peut supprimer plusieurs variables a la fois */
int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_var(env, args[i]);
		i++;
	}
	return (0);
}
