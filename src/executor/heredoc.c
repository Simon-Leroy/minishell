#include "minishell.h"

static char	*init_heredoc_fd(int file_number, int *fd)
{
	char	*filename;

	filename = generate_tmp_filename(file_number);
	if (!filename)
		return (NULL);
	*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		free(filename);
		return (NULL);
	}
	return (filename);
}

static void		heredoc_prompt_loop(char *eof, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			write_heredoc_eof_error(eof);
			break;
		}
		if (ft_strcmp(input, eof) == 0)
		{
			free(input);
			break;
		}
		write_heredoc_input(input, fd);
		free(input);
	}
}

int heredoc_fd(char *eof, int file_number)
{
	char *filename;
	int fd;
	pid_t pid;
	int status;

	filename = init_heredoc_fd(file_number, &fd);
	if (!filename)
		return (-1);
	ignore_signal();
	pid = fork();
	if (pid < 0)
		return (free(filename), close(fd), -1);
	if (pid == 0)
	{
		restore_signal();
		heredoc_prompt_loop(eof, fd);
		close(fd);
		free(filename);
		exit(0);
	}
	close(fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (unlink(filename), free(filename), write(1, "\n", 1), -1);
	return (fd);
}

int	handle_heredoc(t_token *tok, int heredoc_count, t_shell *shell)
{
	int		fd;
	char	*tmp_filename;

	fd = heredoc_fd(tok->next->value, heredoc_count);
	if (fd < 0)
	{
		shell->last_exit_code = 130;
		return (0);
	}
	close(fd);
	tmp_filename = generate_tmp_filename(heredoc_count);
	if (!tmp_filename)
		return (0);
	free(tok->next->value);
	tok->next->value = tmp_filename;
	return (1);
}
