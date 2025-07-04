#include "minishell.h"

int	has_dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*isolate_variable(char *str)
{
	char	*start;
	char	*end;
	char	*variable;
	size_t	i;
	size_t	len;

	start = ft_strchr(str, '$');
	end = start + 1;
	i = 0;
	while (end[i] && (end[i] != '\'' && end[i] != '"' && !check_char(end[i])))
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	if (!variable)
		return (NULL);
	len = i;
	i = 0;
	while (i < len)
	{
		variable[i] = end[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

/* int main()
{
	char *str;
	char *print;

	str = "Bonjour a tous test\"$ USERles copains";
	if (has_dollar_sign(str))
		print = isolate_variable(str);
	printf("%s\n", print);
	return (0);
} */
