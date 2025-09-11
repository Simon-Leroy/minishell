#include "minishell.h"

char	**ft_split_getenv(t_env *env)
{
	char	*path_str;
	char	**paths;

	path_str = get_env_value(env, "PATH");
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*ft_get_abs_path(char *cmd, t_env *env)
{
	char	**env_path;
	char	*temp_path;
	char	*try_path;
	int		i;

	env_path = ft_split_getenv(env);
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

char	*path_handler(char *cmd, t_env *env)
{
	char	*abs_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0 || errno == ENOENT)
			return (ft_strdup(cmd));
		else
			return (ft_strdup(cmd));
	}
	abs_path = ft_get_abs_path(cmd, env);
	return (abs_path);
}

char	*get_path(t_cmd *cmd, t_env *env)
{
	if (!cmd->commands[0])
		return (NULL);
	return (path_handler(cmd->commands[0], env));
}
