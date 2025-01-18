#include "mini.h"

void	redirect_builtin(int cmd ,char **av, t_env *env)
{
	if (cmd == ECHO)
		ft_echo(av);
	else if (cmd == CD)
		ft_cd(av, env);
	else if (cmd == PWD)
		ft_pwd();
	else if (cmd == EXPORT)
		ft_export(av, env);
	else if (cmd == UNSET)
		ft_unset(av, env);
	else if (cmd == ENV)
		ft_env(env);
}

int	redirect_operator(t_cmd *node, char **envp, t_env *env)
{
	int cmd;

	if (!node || !node->tab)
		return(0);
	cmd = which_cmd(node->tab[0]);
	if (cmd == EXIT)
		return(printf("Goodbye! :)\n"), 0);
	else if (cmd == PIPE)
	{
		execute_pipe(node->prev, envp, env);
		if (node->next)  // Skip the next command as it was executed in the pipe
			node->next = node->next->next;
		return(1);
	}
	else if (cmd == EXTERNAL)
		child_process_for_externs(node->tab, envp);
	else if (cmd >= RED_INPUT && cmd <= RED_OUTPUT_APPEND)
		printf("Redirection: %s\n", node->tab[0]);
	else if (cmd >= AND)
		printf("BONUS: %s\n", node->tab[0]);
	else
	{
		printf("Builtin:\n");
		redirect_builtin(cmd, node->tab, env);
	}
	return(1);
}

int	execute_command(t_cmd *cmd, char **envp, t_env *env)
{
	int	command_type;
	char	*path;

	if (!cmd || !cmd->tab)
		return (0);
	command_type = which_cmd(cmd->tab[0]);
	if (command_type == EXIT)
		return (0);
	else if (command_type == EXTERNAL)
	{
		path = find_path(cmd->tab[0]);
		if (!path)
		{
			ft_printf("minishell: command not found: %s\n", cmd->tab[0]);
			exit(1);
		}
		execve(path, cmd->tab, envp);
		free(path);
		exit(1);
	}
	else if (command_type >= RED_INPUT && command_type <= RED_OUTPUT_APPEND)
		printf("Redirection: %s\n", cmd->tab[0]);
	else if (command_type >= AND)
		printf("BONUS: %s\n", cmd->tab[0]);
	else
	{
		redirect_builtin(command_type, cmd->tab, env);
		exit(0);
	}
	return (1);
}
