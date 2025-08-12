#include "minishell.h"

t_redir	*find_last_redir(t_redir *redir, t_token_type type)
{
	t_redir	*last_redir;
	t_redir	*current;

	last_redir = NULL;
	current = redir;
	while (current != NULL)
	{
		if (current->type == type)
			last_redir = current;
		current = current->next;
	}
	return (last_redir);
}

int apply_redirections(t_redir *redir, t_shell *shell)
{
	t_redir *r;
	int fd;

	r = redir;
	while (r)
	{
		if (r->type == INPUT || r->type == HEREDOC)
			fd = open(r->filename, O_RDONLY);
		else if (r->type == OUTPUT)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == APPEND)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (set_exit_code_errno(shell), perror("open failed"), -1);
		if ((r->type == INPUT || r->type == HEREDOC) && dup2(fd, STDIN_FILENO) < 0)
			return (set_exit_code_errno(shell), perror("dup2 failed"), close(fd), -1);
		if ((r->type == OUTPUT || r->type == APPEND) && dup2(fd, STDOUT_FILENO) < 0)
			return (set_exit_code_errno(shell), perror("dup2 failed"), close(fd), -1);
		close(fd);
		if (r->type == HEREDOC)
			unlink(r->filename);
		r = r->next;
	}
	return (0);
}
