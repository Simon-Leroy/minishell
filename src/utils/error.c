#include "minishell.h"

void	set_exit_code_errno(t_shell *shell)
{
	if (errno == ENOENT)
		shell->last_exit_code = 127;
	else if (errno == EACCES)
		shell->last_exit_code = 126;
	else
		shell->last_exit_code = 1;
}
