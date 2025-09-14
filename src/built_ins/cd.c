#include "minishell.h"

static int	count_args(char **args)
{
	int	res;

	res = 0;
	while (args[res])
		res++;
	return (res);
}

static int	cd_alone(t_env *env)
{
	char	*target;
	int		res;

	target = get_env_value(env, "HOME");
	if (!target)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	res = chdir(target);
	if (res == 0)
		return (0);
	perror(target);
	return (1);
}

int	ft_cd(char **args, t_env *env)
{
	int	res;
	int	nbr_args;

	nbr_args = count_args(args);
	if (nbr_args == 1)
		return (cd_alone(env));
	if (nbr_args == 2)
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
	if (nbr_args > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	return (1);
}
