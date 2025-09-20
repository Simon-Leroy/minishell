#include "minishell.h"

void	expand_remove_quotes_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	expand_cmd_args(cmd, shell);
	expand_redirections(cmd->redir, shell);
	remove_quotes_args(cmd);
	remove_quotes_redir(cmd);
	remove_empty_args(cmd);
}
