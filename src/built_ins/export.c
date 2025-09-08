#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*get_export_value(char *str)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
		return (ft_strdup(equal_sign + 1));
	else
		return (ft_strdup(""));
}

char	*get_export_key(char *str)
{
	char	*equal_sign;
	size_t	len;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign != NULL)
		len = equal_sign - str;
	else
		len = ft_strlen(str);
	return (ft_substr(str, 0, len));
}

void	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

void	print_export_error(char *identifier)
{
	write(2, "export: '", 10);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
}
int	ft_export(char **args, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	int		error;

	error = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_export_error(args[i]);
			error = 1;
		}
		else
		{
			key = get_export_key(args[i]);
			value = get_export_value(args[i]);
			set_env(env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (error);
}
