#include "minishell.h"

void	free_mem(t_cmd *cmd, t_token *tokens, char *input)
{
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
	free(input);
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_token *tokens;
	t_cmd	*cmd;
	char	*input;

	(void)argc;
	(void)argv;
	shell.last_exit_code = 0;
	shell.env = init_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = list_tokens(input);
		cmd = link_cmd_redir(tokens);
		run_commands(cmd, &shell);
		free_mem(cmd, tokens, input);
	}
	return (0);
}
