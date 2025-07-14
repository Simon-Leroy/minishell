#include "minishell.h"

/* Extrait le nom d'une variable d'environnement à partir d'une
chaîne contenant un signe $ -> crée une nouvelle str avec juste le nom
de la variable sans le dollar */
char	*isolate_variable(char *str)
{
	char	*start;
	char	*curr;
	char	*variable;
	size_t	i;
	size_t	len;

	start = ft_strchr(str, '$');
	curr = start + 1;
	i = 0;
	while (curr[i] && curr[i] != '$' &&
		curr[i] != '\'' && curr[i] != '"' &&
		!check_char(curr[i]))
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	if (!variable)
		return (NULL);
	len = i;
	i = 0;
	while (i < len)
	{
		variable[i] = curr[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

/* Calcule la longueur de la valeur de la variable d'environnement après
l'expansion.
Incrémente ensuite l'index i, qui sert à parcourir la chaine str, pour le
sortir de la variable avant expansion */
void	incr_env_value_len(char *str, size_t *i, size_t *len)
{
	char	*env_name;
	char	*env_value;

	env_name = isolate_variable(&str[*i]);
	if (env_name)
	{
		env_value = getenv(env_name);
		if (env_value)
			*len += ft_strlen(env_value);
		free(env_name);
	}
	(*i)++;
	while (str[*i] && str[*i] != '$' && !check_char(str[*i]))
		(*i)++;
}

/* Calcule la longueur totale de la chaîne de caractères
après expansion (pour pouvoir malloc) */
size_t	expanded_len(char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			incr_env_value_len(str, &i, &len);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

/* Fonctionne comme incr_env_value_len sauf qu'au lieu de compter le
nombre de caractères on copie la variable d'environnement 'expandue'
dans char *exp */
void	process_env_var(char *str, size_t *i, char *exp, size_t *k)
{
	char	*env_name;
	char	*env_value;
	size_t	j;

	env_name = isolate_variable(&str[*i]);
	if (env_name && env_name[0] != '\0')
	{
		env_value = getenv(env_name);
		if (env_value)
		{
			j = 0;
			while (env_value[j])
			{
				exp[*k] = env_value[j];
				(*k)++;
				j++;
			}
		}
	}
	free(env_name);
	(*i)++;
	while (str[*i] && str[*i] != '$' && !check_char(str[*i]))
		(*i)++;
}

/* Ici on copie toute la chaîne de caractères finale, y compris
tout ce qui n'est pas une variable d'environnement */
void	expand_str_loop(char *str, char *exp)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
			process_env_var(str, &i, exp, &k);
		else
			exp[k++] = str[i++];
	}
	exp[k] = '\0';
}

/* Fonction d'orchestration pour faire l'expansion */
char	*expand_str(char *str)
{
	size_t	len;
	char	*exp;

	len = expanded_len(str);
	exp = malloc(sizeof(char) * (len + 1));
	if (!exp)
		return (NULL);
	expand_str_loop(str, exp);
	return (exp);
}

/* int main()
{
	char *str = "bonjour $USER rebonjour $HOME $TEST";
	char *exp = expand_str(str);
	printf("%s\n", str);
	printf("%s\n", exp);
	free(exp);
} */
