#include "minishell.h"

void	incr_and_copy(char *str, char *new_str, char delim, int *i, int *k)
{
	(*i)++;
	while (str[*i] && str[*i] != delim)
		new_str[(*k)++] = str[(*i)++];
	if (str[*i] == delim)
		(*i)++;
}

size_t	len_without_quotes(char *str)
{
	size_t	len;
	size_t	i;
	int		in_single;
	int		in_double;

	i = 0;
	len = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_double == 0)
		{
			in_single = !in_single;
			i++; // on ignore la quote
		}
		else if (str[i] == '"' && in_single == 0)
		{
			in_double = !in_double;
			i++; // on ignore la quote
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		k;
	int		in_single;
	int		in_double;

	new_str = malloc(len_without_quotes(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else
			new_str[k++] = str[i++];
	}
	new_str[k] = '\0';
	return (new_str);
}
