#include "mini.h"

void	print_my_envp(t_env *env)
{
	while (env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = NULL;
	init_envp(&env, envp);
	print_my_envp(env);
	return (0);
}