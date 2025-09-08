#include "minishell.h"

t_env *init_env(char **envp)
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

int	ft_env(t_shell *shell)
{
	print_env(shell->env);
	return (0); // exit code
}
