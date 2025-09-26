/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 01:52:31 by roguille          #+#    #+#             */
/*   Updated: 2025/09/26 14:46:33 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

void	free_mem(t_cmd *cmd, t_token *tokens, char *input)
{
	ft_free_tokens(tokens);
	ft_free_full_cmd(cmd);
	free(input);
}

static char	*read_input(t_shell *shell)
{
	char	*input;

	input = readline("minishell> ");
	if (!input)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	if (g_signal == SIGINT)
	{
		shell->last_exit_code = 130;
		g_signal = 0;
	}
	if (*input)
		add_history(input);
	return (input);
}

static void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = list_tokens(input, shell);
	cmd = link_cmd_redir(tokens, shell);
	if (cmd)
		run_commands(cmd, shell);
	free_mem(cmd, tokens, input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell.last_exit_code = 0;
	shell.env = init_env(envp);
	setup_signal();
	while (1)
	{
		input = read_input(&shell);
		if (!input)
			break ;
		process_input(input, &shell);
	}
	rl_clear_history();
	ft_free_env(shell.env);
	return (0);
}
