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
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, int last_status)
{
	int	args_nbr;
	int	code;

	args_nbr = args_count(args);
	if (!args[1])
		exit(last_status);
	if (args_nbr >= 3)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	if (args[1] && !is_numeric(args[1]))
	{
		printf("numeric argument required\n");
		exit(2);
	}
	code = ft_atoi(args[1]);
	exit(code);
}
