#include "minishell.h"

void	copy_env_var_type(char **str, char **exp, t_env *env)
{
	char	*var_name;
	char	*var_value;
	size_t	j;

	var_name = extract_var_name(*str);
	if (var_name)
	{
		var_value = get_env_value(env, var_name);
		if (var_value)
		{
			j = 0;
			while (var_value[j])
				*(*exp)++ = var_value[j++];
		}
		free(var_name);
	}
	(*str)++;
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
}

/* void	copy_env_var_type(char *str, size_t *i, char *exp,
			size_t *k, t_env *env)
{
	char	*var_name;
	char	*var_value;
	size_t	j;

	var_name = extract_var_name(&str[*i]);
	if (var_name)
	{
		var_value = get_env_value(env, var_name);
		if (var_value)
		{
			j = 0;
			while (var_value[j])
				exp[(*k)++] = var_value[j++];
		}
		free(var_name);
	}
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
} */

void	process_env_var_copy(char **str, char **exp, t_shell *shell)
{
	char	*var_value;
	size_t	j;

	if (classify_dollar((*str)[1]) == ENV_VAR)
		copy_env_var_type(str, exp, shell->env);
	else if (classify_dollar((*str)[1]) == EXIT_STATUS)
	{
		var_value = ft_itoa(shell->last_exit_code);
		if (!var_value)
			return ;
		j = 0;
		while (var_value[j])
			*(*exp)++ = var_value[j++];
		free(var_value);
		*str += 2;
	}
	else if (classify_dollar((*str)[1]) == LITERAL)
		*(*exp)++ = *(*str)++;
	else if (classify_dollar((*str)[1]) == INVALID)
		*str += 2;
}
