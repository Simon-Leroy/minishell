#include "minishell.h"

char	**ft_split_getenv(void)
{
	char	*path_str;
	char	**paths;

	path_str = getenv("PATH");
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*ft_get_abs_path(char *cmd)
{
	char	**env_path;
	char	*temp_path;
	char	*try_path;
	int		i;

	env_path = ft_split_getenv();
	if (!env_path)
		return (NULL);
	i = 0;
	while (env_path[i])
	{
		temp_path = ft_strjoin(env_path[i], "/");
		if (!temp_path)
			break ;
		try_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!try_path)
			break ;
		if (access(try_path, F_OK) == 0)
			return (ft_free_tab(env_path), try_path);
		free(try_path);
		i++;
	}
	ft_free_tab(env_path);
	return (NULL);
}

char	*path_handler(char *cmd)
{
	char	*abs_path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	else
	{
		abs_path = ft_get_abs_path(cmd);
		return (abs_path);
	}
}
