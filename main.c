#include "mini.h"

void	ft_echo(char **av);
void	ft_env(t_env *env);
void	ft_pwd(void);
void	ft_cd(char **av, t_env *env);
void	ft_export(char **av, t_env *env);
void	ft_unset(char **av, t_env *env);

int main(int ac, char **av, char **envp)
{
	char 	*line;
	t_env	*env;

	(void)ac;
	(void)av;
	line = readline(PROMPT);
	env = NULL;
	init_envp(&env, envp);
	while(ft_strncmp(line, "exit", 4))
	{
		if (*line)
		{
			if (ft_strncmp(line, "echo", 4) == 0)
			{
				printf("built-in echo\n");
				ft_echo(ft_split(line, ' '));
			}
			else if (ft_strncmp(line, "env", 4) == 0)
			{
				printf("built-in env\n");
				ft_env(env);
			}
			else if (ft_strncmp(line, "pwd", 3) == 0)
			{
				printf("built-in pwd\n");
				ft_pwd();
			}
			else if (ft_strncmp(line, "cd", 2) == 0)
			{
				printf("built-in cd\n");
				ft_cd(ft_split(line, ' '), env);
			}
			else if (ft_strncmp(line, "export", 6) == 0)
			{
				printf("built-in export\n");
				ft_export(ft_split(line, ' '), env);
			}
			else if (ft_strncmp(line, "unset", 5) == 0)
			{
				printf("built-in unset\n");
				ft_unset(ft_split(line, ' '), env);
			}
			else
				child_process_for_externs(line, envp);
			add_history(line);
			free(line);
		}
		line = readline(PROMPT);
	}
	clear_history();
	free(line);
	return (0);
}