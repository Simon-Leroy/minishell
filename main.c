#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *test;
	t_token *tokens;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	test = "echo \"$USER est un enorme bg\"";
	tokens = list_tokens(test);
	cmd = link_cmd_redir(tokens);
	expand_cmd(cmd);
	run_commands(cmd, envp);
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
}
