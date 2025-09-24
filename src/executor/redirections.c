/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:14 by roguille          #+#    #+#             */
/*   Updated: 2025/09/24 17:01:33 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	apply_redirections(t_redir *redir, t_shell *shell)
{
	t_redir	*r;
	int		fd;

	r = redir;
	fd = -1;
	while (r)
	{
		if (r->type == INPUT || r->type == HEREDOC)
			fd = open(r->filename, O_RDONLY);
		else if (r->type == OUTPUT)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == APPEND)
			fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (exit_errno(shell), perror(r->filename), -1);
		if ((r->type == INPUT || r->type == HEREDOC) && dup2(fd, 0) < 0)
			return (exit_errno(shell), perror(r->filename), close(fd), -1);
		if ((r->type == OUTPUT || r->type == APPEND) && dup2(fd, 1) < 0)
			return (exit_errno(shell), perror(r->filename), close(fd), -1);
		close(fd);
		if (r->type == HEREDOC)
			unlink(r->filename);
		r = r->next;
	}
	return (0);
}
