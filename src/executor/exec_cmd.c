/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:51:04 by roguille          #+#    #+#             */
/*   Updated: 2025/09/29 12:49:12 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_fail(t_shell *shell, char *path, int exit_code, char **envp)
{
	perror("minishell");
	shell->last_exit_code = exit_code;
	if (path)
		free(path);
	if (envp)
		ft_free_tab(envp);
	exit(exit_code);
}
/*
Fonction d'exécution des commandes

1) Si la commande est vide, on stoppe
2) Si les redirections échouent, exit 1
3) On teste les built-ins, si ça renvoie -1 c'est que la
commande n'est pas une built-in
4) Si c'est une built-in, elle est exécutée et on exit avec
le code de retour de la built-in
5) Sinon on continue et on récupère le chemin d'accès de la commande
à exécuter
6) On vérifie que le chemin d'accès est valide et bien trouvé
7) On construit le tableau des var d'environnement à passer à execve
8) On exécute la commande avec execve
*/

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;
	int		ret;

	expand_remove_quotes_cmd(cmd, shell);
	if (!cmd->commands[0] || cmd->commands[0][0] == '\0')
	{
		shell->last_exit_code = 0;
		return ;
	}
	if (apply_redirections(cmd->redir, shell) < 0)
		exit(1);
	ret = exec_builtin(cmd, shell);
	if (ret != -1)
		exit(ret);
	path = get_path(cmd, shell->env);
	check_path(cmd->commands[0], path, shell);
	envp = build_envp(shell->env);
	if (!envp)
		handle_fail(shell, path, 1, NULL);
	if (execve(path, cmd->commands, envp) == -1)
		handle_fail(shell, path, 126, envp);
	free(path);
}
