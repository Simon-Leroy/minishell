#include "minishell.h"

void	exec_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd->commands[0])
	{
//		ft_free_tab(cmd->commands);
		perror("could not find command");
		exit(127);
	}
	path = path_handler(cmd->commands[0]);
	if (!path)
	{
//		ft_free_tab(args);
		perror("could not find command");
		exit(127);
	}
	execve(path, cmd->commands, envp);
	perror("execve failed");
	free(path);
//	ft_free_tab(args);
	exit(EXIT_FAILURE);
}

/* int main(int argc, char **argv, char **envp)
{
	char *test = "cat -e Makefile";

	(void)argc;
	(void)argv;

	t_token *tokens;
	t_cmd	*cmd;
	t_cmd	*tmp;

	tokens = list_tokens(test);
	cmd = link_cmd_redir(tokens);
 	tmp = cmd;
	while (tmp)
	{
		printf("Command:\n");
		for (int i = 0; tmp->commands[i]; i++)
			printf("  - %s\n", tmp->commands[i]);
		t_redir *r = tmp->redir;
		while (r)
		{
			printf("  Redirection: type %d → %s\n", r->type, r->filename);
			r = r->next;
		}
		tmp = tmp->next;
	}
	exec_cmd(cmd, envp);
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
} */
