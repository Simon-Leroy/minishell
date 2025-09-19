#include "minishell.h"

int	ft_pwd(void)
{
	char	dir[PATH_MAX];

	if (getcwd(dir, PATH_MAX))
	{
		printf("%s\n", dir);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
