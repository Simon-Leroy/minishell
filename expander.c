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

void	string_replace(char *source, char *substring, char *with)
{
	char	*substring_source;

	substring_source = ft_strchr(source, '$') + 1;
	if (substring_source == NULL)
		return ;
	ft_memmove(substring_source + ft_strlen(with),
				substring_source + strlen(substring),
				strlen(substring_source) - strlen(substring) + 1);
	ft_memcpy(substring_source, with, strlen(with));
}

int main()
{
	char str[100] = "Bonjour a tous test $USER copains";
//	char *start;
//	char *print;
//	char *test;
/* 	size_t i;

	start = ft_strchr(str, '$');
	while (start[i] && (start[i] != '\'' && start[i] != '"' && !check_char(start[i])))
		i++; */

	printf("%s\n", str);
	string_replace(str, isolate_variable(str), getenv(isolate_variable(str)));
	printf("%s\n", str);
/* 	str = "Bonjour a tous test $USER copains";
	printf("strstr : %s\n", strstr(str, "USER"));
	test = ft_strnstr(str, isolate_variable(str), ft_strlen(isolate_variable(str)));
	printf("%s\n", ft_strchr(str, '$'));
	print = NULL;
	if (has_dollar_sign(str))
		print = isolate_variable(str);
	printf("%s\n", print);
	printf("%s\n", getenv(print));
	printf("%s\n", test);
	return (0); */
}
