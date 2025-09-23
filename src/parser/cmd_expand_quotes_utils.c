/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguille <roguille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:41 by roguille          #+#    #+#             */
/*   Updated: 2025/09/23 01:51:43 by roguille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_args(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;
	t_cmd	*tmp;

	tmp = cmd;
	i = 0;
	while (tmp->commands && tmp->commands[i])
	{
		if (ft_strchr(tmp->commands[i], '$'))
		{
			expanded = expand_str(tmp->commands[i], shell);
			free(tmp->commands[i]);
			tmp->commands[i] = expanded;
		}
		i++;
	}
}

void	expand_redirections(t_redir *redir, t_shell *shell)
{
	t_redir	*tmp_redir;
	char	*expanded;

	tmp_redir = redir;
	while (tmp_redir)
	{
		if (ft_strchr(tmp_redir->filename, '$'))
		{
			expanded = expand_str(tmp_redir->filename, shell);
			free(tmp_redir->filename);
			tmp_redir->filename = expanded;
		}
		tmp_redir = tmp_redir->next;
	}
}

void	remove_quotes_args(t_cmd *cmd)
{
	int		i;
	char	*no_quotes;

	if (!cmd || !cmd->commands)
		return ;
	i = 0;
	while (cmd->commands[i])
	{
		no_quotes = remove_quotes(cmd->commands[i]);
		free(cmd->commands[i]);
		cmd->commands[i] = no_quotes;
		i++;
	}
}

void	remove_quotes_redir(t_cmd *cmd)
{
	t_redir	*tmp_redir;
	char	*no_quotes;

	if (!cmd || !cmd->redir)
		return ;
	tmp_redir = cmd->redir;
	while (tmp_redir)
	{
		if (tmp_redir->filename)
		{
			no_quotes = remove_quotes(tmp_redir->filename);
			free(tmp_redir->filename);
			tmp_redir->filename = no_quotes;
		}
		tmp_redir = tmp_redir->next;
	}
}

void	remove_empty_args(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->commands[i])
	{
		if (cmd->commands[i][0] != '\0')
			cmd->commands[j++] = cmd->commands[i];
		else
			free(cmd->commands[i]);
		i++;
	}
	cmd->commands[j] = NULL;
}
