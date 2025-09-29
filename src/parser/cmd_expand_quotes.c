/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:40 by roguille          #+#    #+#             */
/*   Updated: 2025/09/28 22:42:16 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Wrapper pour gérer toutes les expansions */
void	expand_remove_quotes_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
		return ;
	expand_cmd_args(cmd, shell);
	expand_redirections(cmd->redir, shell);
	remove_quotes_args(cmd);
	remove_quotes_redir(cmd);
	remove_empty_args(cmd);
}
