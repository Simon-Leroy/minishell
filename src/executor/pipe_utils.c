#include "minishell.h"

void	close_pipe(int *fd)
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
}

void	check_close(int fd)
{
	if (fd >= 0)
		close(fd);
}
