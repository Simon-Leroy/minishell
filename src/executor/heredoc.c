#include "minishell.h"

char	*generate_tmp_filename(int	i)
{
	char	*prefix;
	char	*nbr;
	char	*filename;

	prefix = "/tmp/.heredoc_";
	nbr = ft_itoa(i);
	if (!nbr)
		return (NULL);
	filename = ft_strjoin(prefix, nbr);
	free(nbr);
	return (filename);
}

void	write_heredoc_input(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static void	write_heredoc_eof_error(char *eof)
{
	write(2, "minishell: ", 11);
	write(2, "warning: here-document delimited by end-of-file ", 48);
	write(2, "(wanted '", 9);
	write(2, eof, ft_strlen(eof));
	write(2,"')\n", 3);
}

int heredoc_fd(char *eof, int file_number)
{
	char *filename = generate_tmp_filename(file_number);
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid_t pid;
	int status;

	if (fd < 0)
		return (free(filename), -1);
	ignore_signal();
	pid = fork();
	if (pid < 0)
		return (free(filename), close(fd), -1);
	if (pid == 0)
	{
		restore_signal();
		char *input;
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
