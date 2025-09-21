#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tokens(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list->next;
		free(list->value);
		free(list);
		list = temp;
	}
}

void	ft_free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		free(redir->filename);
		free(redir);
		redir = temp;
	}
}

void	ft_free_full_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->commands)
		{
			i = 0;
			while (cmd->commands[i])
			{
				free(cmd->commands[i]);
				i++;
			}
			free(cmd->commands);
		}
		if (cmd->redir)
			ft_free_redir(cmd->redir);
		free(cmd);
		cmd = temp;
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
