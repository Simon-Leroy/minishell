/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:50:54 by roguille          #+#    #+#             */
/*   Updated: 2025/09/27 10:22:01 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Si name est le nom d'un builtin !ft_strcmp(name, builtin) renvoie
un int different de 0
Ici uniquement les built ins qui s'executent en dehors d'un child process
*/
int	is_parent_builtin(char *name)
{
	return (!ft_strcmp(name, "exit") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "env") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "unset"));
}

/*
Fonction pour détecter et exécuter les built-ins lorsqu'ils sont
entrés dans une commande du terminal
*/
int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	if (!cmd || !cmd->commands || !cmd->commands[0])
		return (-1);
	name = cmd->commands[0];
	if (ft_strcmp(name, "exit") == 0)
		return (ft_exit(cmd->commands, shell->last_exit_code));
	if (ft_strcmp(name, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(name, "echo") == 0)
		return (ft_echo(cmd->commands));
	if (ft_strcmp(name, "cd") == 0)
		return (ft_cd(cmd->commands, shell->env));
	if (ft_strcmp(name, "env") == 0)
		return (ft_env(shell));
	if (ft_strcmp(name, "export") == 0)
		return (ft_export(cmd->commands, &shell->env));
	if (ft_strcmp(name, "unset") == 0)
		return (ft_unset(cmd->commands, &shell->env));
	return (-1);
}
