#include "minishell.h"

static int	count_args(char **args)
{
	int	res;

	res = 0;
	while (args[res])
		res++;
	return (res);
}

int	ft_cd(char **args)
{
	int	res;

	if (count_args(args) == 2)
	{
		res = chdir(args[1]);
		if (res == 0)
			return (0);
		if (res < 0)
		{
			perror(args[1]);
			return (1);
		}
	}
	return (1);
}