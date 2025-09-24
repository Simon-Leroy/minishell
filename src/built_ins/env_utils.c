/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:51 by roguille          #+#    #+#             */
/*   Updated: 2025/09/24 15:28:27 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_count(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static int	update_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				return (0);
			return (1);
		}
		env = env->next;
	}
	return (-1);
}

int	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_node;
	int		status;

	if (!key || !value)
		return (0);
	tmp = *env;
	status = update_env_value(*env, key, value);
	if (status >= 0)
		return (status);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
		return (free(new_node->key), free(new_node->value), free(new_node), 0);
	new_node->next = *env;
	*env = new_node;
	return (1);
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		else
			printf("%s=\n", tmp->key);
		tmp = tmp->next;
	}
}
