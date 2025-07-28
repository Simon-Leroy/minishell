#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char *test;
	t_token *tokens;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	shell.last_exit_code = 0;
	test = "cata caca";
	tokens = list_tokens(test);
	cmd = link_cmd_redir(tokens);
	expand_cmd(cmd);
	run_commands(cmd, envp, &shell);
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
	printf("%d\n", shell.last_exit_code);
}
