#include "mini.h"

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			//ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	//ft_free_split(paths);
	return (NULL);
}

int	handle_extern_command(char *line, char **envp)
{
	pid_t	pid;
	char	**av_command;
	char	*path;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		av_command = ft_split(line, ' ');
		path = find_path(av_command[0], envp);
		if (!path)
			printf("command not found booouuh looser");
		else
			execve(path, av_command, envp);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char *line;
	line = readline("dis moi tout > ");
	while(1)
	{
		if (handle_extern_command(line, envp))
			ft_printf("\n");
		add_history(line);
		free(line);
		line = readline("dis moi tout > ");
	}
	clear_history();
	free(line);
	(void)ac;
	(void **)av;
	return (0);
}