#include "minishell.h"

void	copy_env_var_type(char *str, size_t *i, char *exp, size_t *k, t_env *env)
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
	(*i)++; // on passe au caractère juste après le dollar
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
		(*i)++; // on sort du nom de la variable
}
void	process_env_var_copy(char *str, size_t *i, char *exp, size_t *k, t_shell *shell)
{
	char	*var_value;
	size_t	j;

	if (classify_dollar(str[*i + 1]) == ENV_VAR)
		copy_env_var_type(str, i, exp, k, shell->env);
	else if (classify_dollar(str[*i + 1]) == EXIT_STATUS)
	{
		var_value = ft_itoa(shell->last_exit_code);
		if (!var_value)
			return ;
		j = 0;
		while (var_value[j])
			exp[(*k)++] = var_value[j++];
		free(var_value);
		(*i) += 2;
	}
	else if (classify_dollar(str[*i + 1]) == LITERAL)
		exp[(*k)++] = str[(*i)++]; // copie le dollar
	else if (classify_dollar(str[*i + 1]) == INVALID)
		*i += 2; // on skip le dollar le caractère invalide
}
