#include "minishell.h"

char	*generate_tmp_filename(int i)
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

void	write_heredoc_eof_error(char *eof)
{
	write(2, "minishell: ", 11);
	write(2, "warning: here-document delimited by end-of-file ", 48);
	write(2, "(wanted '", 9);
	write(2, eof, ft_strlen(eof));
	write(2, "')\n", 3);
}
