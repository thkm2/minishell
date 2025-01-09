#include "mini.h"

int main(int ac, char **av, char **envp)
{
	char 	*line;

	(void)ac;
	(void)av;
	line = readline(" >");
	while(ft_strncmp(line, "exit", 4))
	{
		if (*line)
		{
			// ici
			add_history(line);
			free(line);
		}
		line = readline(" >");
	}
	clear_history();
	free(line);
	return (0);
}