#include "minishell.h"

void	print_error(char *command, int exit_code)
{
	if (exit_code == 127)
	{
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
	}
	else if (exit_code == 127)
		write(2, "Permission denied\n", 18);
}

void	set_exit_code_errno(t_shell *shell)
{
	if (errno == ENOENT)
		shell->last_exit_code = 127;
	else if (errno == EACCES)
		shell->last_exit_code = 126;
	else
		shell->last_exit_code = 1;
}
