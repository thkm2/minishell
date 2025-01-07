#include "mini.h"

void	child_process_for_externs(char *s, char **envp);

int main(int ac, char **av, char **envp)
{
	char *line;
	line = readline("dis moi tout > ");
	while(1)
	{
		child_process_for_externs(line, envp);
		add_history(line);
		free(line);
		line = readline("dis moi tout > ");
	}
	clear_history();
	free(line);
	ac++;
	av++;
	return (0);
}