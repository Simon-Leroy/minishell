#include "minishell.h"

void	write_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	exit_errno(t_shell *shell)
{
	if (errno == ENOENT)
		shell->last_exit_code = 127;
	else if (errno == EACCES)
		shell->last_exit_code = 126;
	else
		shell->last_exit_code = 1;
}
