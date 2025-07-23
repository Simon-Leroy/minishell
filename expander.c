#include "minishell.h"

t_env_var_type classify_dollar(char c)
{
	if (c == '?')
		return (EXIT_STATUS);
	else if (isalpha(c) || c == '_')
		return (ENV_VAR);
	else if (isdigit(c))
		return (INVALID);
	else
		return (LITERAL);
}

char	*extract_var_name(char *str)
{
	char			*s;
	t_env_var_type	type;
	size_t			i;

	s = ft_strchr(str, '$');
	if (!s )
		return (NULL);
	s++;
	type = classify_dollar(s[0]);
	i = 0;
	if (type == ENV_VAR)
	{
		while (s[i] && (isalnum(s[i]) || s[i] == '_'))
			i++;
		return (ft_substr(s, 0, i));
	}
	if (type == LITERAL)
		return (ft_strdup("$"));
	if (type == EXIT_STATUS)
		return (ft_strdup("?"));
	return (ft_strdup(""));
}

// $? pas gere pour le moment
void	process_var_len(char *str, size_t *i, size_t *len)
{
	char	*var_name;
	char	*var_value;

	if (classify_dollar(str[*i + 1]) == ENV_VAR)
	{
		var_name = extract_var_name(&str[*i]);
		if (var_name)
		{
			var_value = getenv(var_name);
			if (var_value)
				*len += ft_strlen(var_value);
			free(var_name);
		}
		(*i)++; // on passe au caractère juste après le dollar
		while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
			(*i)++; // on sort du nom de la variable
	}
	else if (classify_dollar(str[*i + 1]) == LITERAL)
	{
		(*len)++; //on compte le caractère dollar
		(*i)++; // on passe au caractère juste après le dollar
	}
	else if (classify_dollar(str[*i + 1]) == INVALID || classify_dollar(str[*(i + 1)]) == EXIT_STATUS)
		*i += 2; // on skip le dollar le caractère invalide
}

size_t	expanded_len(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
			process_var_len(str, &i, &len);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	process_env_var_copy(char *str, size_t *i, char *exp, size_t *k)
{
	char	*var_name;
	char	*var_value;
	size_t	j;

	if (classify_dollar(str[*i + 1]) == ENV_VAR)
	{
		var_name = extract_var_name(&str[*i]);
		if (var_name)
		{
			var_value = getenv(var_name);
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
	else if (classify_dollar(str[*i + 1]) == LITERAL)
		exp[(*k)++] = str[(*i)++]; // copie le dollar
	else if (classify_dollar(str[*i + 1]) == INVALID || classify_dollar(str[*(i + 1)]) == EXIT_STATUS)
		*i += 2; // on skip le dollar le caractère invalide
}

char	*expand_str(char *str)
{
	char	*exp;
	size_t	len;
	size_t	i;
	size_t	k;

	len = expanded_len(str);
	exp = malloc(sizeof(char) * (len + 1));
	if (!exp)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
			process_env_var_copy(str, &i, exp, &k);
		else
			exp[k++] = str[i++];
	}
	exp[k] = '\0';
	return (exp);
}

/* int main()
{
	char *str = "bonjour $USER$USER $ $9HOME";
	char *expand = expand_str(str);

	printf("%li\n", expanded_len(str));
	printf("%s\n", expand);
	free(expand);
} */
