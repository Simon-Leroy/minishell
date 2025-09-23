/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:49 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:50:51 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	char	*equal;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
			set_env(&env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (env);
}

char	*join_key_value(char *key, char *value)
{
	char	*str;
	size_t	len;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, key, len);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, value, len);
	return (str);
}

static void	free_tab(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

char	**build_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		count;
	int		i;

	count = env_count(env);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (i < count)
	{
		envp[i] = join_key_value(tmp->key, tmp->value);
		if (!envp[i])
		{
			free_tab(envp, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}

int	ft_env(t_shell *shell)
{
	print_env(shell->env);
	return (0);
}
