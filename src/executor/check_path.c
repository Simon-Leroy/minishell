#include "minishell.h"

void check_command_not_found(char *cmd, char *path, t_shell *shell)
{
	if (!path && !ft_strchr(cmd, '/'))
	{
		write_error(cmd, "command not found");
		shell->last_exit_code = 127;
		exit(shell->last_exit_code);
	}
}

void check_no_such_file(char *cmd, char *path, t_shell *shell)
{
	struct stat s;

	if (ft_strchr(cmd, '/') && stat(path, &s) == -1)
	{
		write_error(cmd, "No such file or directory");
		shell->last_exit_code = 127;
		exit(shell->last_exit_code);
	}
}

void check_is_directory(char *cmd, char *path, t_shell *shell)
{
	struct stat s;

	if (stat(path, &s) == 0 && S_ISDIR(s.st_mode))
	{
		write_error(cmd, "Is a directory");
		shell->last_exit_code = 126;
		exit(shell->last_exit_code);
	}
}

void check_permission_denied(char *cmd, char *path, t_shell *shell)
{
	if (access(path, X_OK) != 0)
	{
		write_error(cmd, "Permission denied");
		shell->last_exit_code = 126;
		exit(shell->last_exit_code);
	}
}

void check_path(char *cmd, char *path, t_shell *shell)
{
    // Case 1: path contains '/' → explicit path
    if (ft_strchr(cmd, '/'))
    {
        // file does not exist
        if (!path || access(path, F_OK) != 0)
        {
            write_error(cmd, "No such file or directory");
            shell->last_exit_code = 127;
            exit(shell->last_exit_code);
        }

        check_is_directory(cmd, path, shell);
        check_permission_denied(cmd, path, shell);
    }
    // Case 2: command without '/' → search in PATH
    else
    {
        check_command_not_found(cmd, path, shell);
    }
}


