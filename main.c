#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
//	char *test;
	t_token *tokens;
	t_cmd	*cmd;
	char	*input;

	(void)argc;
	(void)argv;
	shell.last_exit_code = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		tokens = list_tokens(input);
		cmd = link_cmd_redir(tokens);
		run_commands(cmd, envp, &shell);
		ft_free_tokens(tokens);
		ft_free_full_cmd(cmd);
	}
	return (0);
}
