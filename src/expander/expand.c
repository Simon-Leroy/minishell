#include "minishell.h"

char	*alloc_expanded_str(char *str, t_shell *shell)
{
	size_t	len;
	char	*exp;

	len = expanded_len(str, shell);
	exp = malloc(sizeof(char) * (len + 1));
	if (!exp)
		return (NULL);
	return (exp);
}

char	*expand_str(char *str, t_shell *shell)
{
	char	*exp;
	size_t	i;
	size_t	k;
	int		in_single;
	int		in_double;

	exp = alloc_expanded_str(str, shell);
	if (!exp)
		return (NULL);
	i = 0;
	k = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_double == 0)
		{
			in_single = !in_single;
			exp[k++] = str[i++];
		}
		else if (str[i] == '"' && in_single == 0)
		{
			in_double = !in_double;
			exp[k++] = str[i++];
		}
		else if (in_single == 0 && str[i] == '$')
			process_env_var_copy(str, &i, exp, &k, shell);
		else
			exp[k++] = str[i++];
	}
	exp[k] = '\0';
	return (exp);
}

/* int main()
{
	t_shell	shell;

	shell.last_exit_code = 127;
	char *str = "bonjour $USER$USER $?abcdef $9HOME";
	char *expand = expand_str(str, &shell);

	printf("%li\n", expanded_len(str, &shell));
	printf("%li\n", ft_strlen(expand));
	printf("%s\n", expand);
	free(expand);
} */
