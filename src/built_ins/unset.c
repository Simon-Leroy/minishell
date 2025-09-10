#include "minishell.h"

void	free_env_var(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

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
