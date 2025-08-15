#include "minishell.h"

char	*generate_tmp_filename(int	i)
{
	char	*prefix;
	char	*nbr;
	char	*filename;

	prefix = "/tmp/.heredoc_";
	nbr = ft_itoa(i);
	filename = ft_strjoin(prefix, nbr);
	free(nbr);
	return (filename);
}

void	write_heredoc_input(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int		heredoc_fd(char *eof, int file_number)
{
	char	*input;
	char	*filename;
	int		fd;

	filename = generate_tmp_filename(file_number);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			break ;
		}
		if (ft_strcmp(input, eof) == 0)
			return (close(fd), free(input), free(filename), fd);
		write_heredoc_input(input, fd);
		free(input);
	}
	return (close(fd), free(input), free(filename), -1);
}

int	handle_heredoc(t_token *tok, int heredoc_count)
{
	int		fd;
	char	*tmp_filename;

	fd = heredoc_fd(tok->next->value, heredoc_count);
	if (fd < 0)
	{
		perror("heredoc failed");
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
/*
int main()
{
	heredoc_fd("bonjour", 1);
	return (0);
}

int main()
{
	char	*eof;
	char	*input;
	int		fd;

	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	eof = readline("minishell> ");
	input = readline("> ");
	if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		free(eof);
		free(input);
		return (0);
	}
	write_heredoc_input(input, fd);
	while (ft_strncmp(input, eof, ft_strlen(eof)) != 0)
	{
		input = readline("> ");
		if (!input)
			break ;
		write_heredoc_input(input, fd);
	}
	free(eof);
	free(input);
	return (0);
} */
