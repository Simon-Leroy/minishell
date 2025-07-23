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

/* int	redirect_input(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror("could not open file");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output(t_redir *redir)
{
	int fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("could not open file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_append(t_redir *redir)
{
	int fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("could not open file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	open_output_file(char *filename, int *last_fd)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open output failed");
		return (-1);
	}
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = fd;
	return (0);
}

int apply_all_output_redir(t_redir *redir)
{
	t_redir *current;
	int last_fd;

	last_fd = -1;
	current = redir;
	while (current)
	{
		if (current->type == OUTPUT)
		{
			if (open_output_file(current->filename, &last_fd) == -1)
				return (-1);
		}
		current = current->next;
	}
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDOUT_FILENO) < 0)
			return (perror("dup2 failed"), close(last_fd), -1);
		close(last_fd);
	}
	return (0);
}

int	open_append_file(char *filename, int *last_fd)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open append failed");
		return (-1);
	}
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = fd;
	return (0);
}

int apply_all_append_redir(t_redir *redir)
{
	t_redir *current;
	int last_fd;

	last_fd = -1;
	current = redir;
	while (current)
	{
		if (current->type == APPEND)
		{
			if (open_append_file(current->filename, &last_fd) == -1)
				return (-1);
		}
		current = current->next;
	}
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDOUT_FILENO) < 0)
			return (perror("dup2 failed"), close(last_fd), -1);
		close(last_fd);
	}
	return (0);
}

int	open_input_file(char *filename, int *last_fd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open input failed");
		return (-1);
	}
	if (*last_fd != -1)
		close(*last_fd);
	*last_fd = fd;
	return (0);
}

int apply_all_input_redir(t_redir *redir)
{
	t_redir *current;
	int last_fd;

	last_fd = -1;
	current = redir;
	while (current)
	{
		if (current->type == INPUT)
		{
			if (open_input_file(current->filename, &last_fd) == -1)
				return (-1);
		}
		current = current->next;
	}
	if (last_fd != -1)
	{
		if (dup2(last_fd, STDIN_FILENO) < 0)
			return (perror("dup2 failed"), close(last_fd), -1);
		close(last_fd);
	}
	return (0);
}

int redirect(t_cmd *cmd)
{
	if (apply_all_input_redir(cmd->redir) == -1)
		return (-1);
	if (apply_all_output_redir(cmd->redir) == -1)
		return (-1);
	if (apply_all_append_redir(cmd->redir) == -1)
		return (-1);
	return (0);
} */

int apply_redirections(t_redir *redir)
{
	t_redir *r = redir;
	int fd;

	while (r)
	{
		if (r->type == INPUT)
			fd = open(r->filename, O_RDONLY);
		else if (r->type == OUTPUT)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == APPEND)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("open failed"), -1);
		if (r->type == INPUT && dup2(fd, STDIN_FILENO) < 0)
			return (perror("dup2 failed"), close(fd), -1);
		if ((r->type == OUTPUT || r->type == APPEND)
			&& dup2(fd, STDOUT_FILENO) < 0)
			return (perror("dup2 failed"), close(fd), -1);
		close(fd);
		r = r->next;
	}
	return (0);
}


/* int	redirect(t_cmd *cmd)
{
	t_redir	*redir_cmd;
	t_redir	*last_redir;

	redir_cmd = cmd->redir;
	last_redir = find_last_redir(redir_cmd, INPUT);
	if (last_redir && redirect_input(last_redir) == -1)
		return (-1);
	last_redir = find_last_redir(redir_cmd, OUTPUT);
	if (last_redir && redirect_output(last_redir) == -1)
		return (-1);
	last_redir = find_last_redir(redir_cmd, APPEND);
	if (last_redir && redirect_append(last_redir) == -1)
		return (-1);
	return (0);
} */
