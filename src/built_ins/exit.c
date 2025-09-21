#include "minishell.h"

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, int last_status)
{
	int		args_nbr;
	int		code;
	char	*first_arg;

	args_nbr = args_count(args);
	if (!args[1])
		exit(last_status);
	first_arg = remove_quotes(args[1]);
	if (args_nbr >= 3)
	{
		write(2, " too many arguments\n", 20);
		exit(1);
	}
	if (first_arg && !is_numeric(first_arg))
	{
		write(2, " numeric argument required\n", 27);
		exit(2);
	}
	code = ft_atoi(first_arg);
	free(first_arg);
	exit((unsigned char)code);
}
