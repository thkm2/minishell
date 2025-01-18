/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:35:20 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/18 16:40:23 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	execute_pipe(t_cmd *cmd, char **envp, t_env *env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int     status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("fork"), 0);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipefd[1]);
			exit(1);
		}
		close(pipefd[1]);
		setenv("IN_PIPE", "1", 1);
		execute_command(cmd, envp, env);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (perror("fork"), 0);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(pipefd[0]);
			exit(1);
		}
		close(pipefd[0]);
		setenv("IN_PIPE", "1", 1);
		execute_command(cmd->next->next, envp, env);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (1);
}
