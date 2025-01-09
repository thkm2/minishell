#ifndef MINI_H
# define MINI_H

// libft
# include "libft/libft.h"

// libc
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

// new ****
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;
void	ft_free_split(char **tab);
void	add_env_node(t_env **env, char *name, char *value);
void	init_envp(t_env **env, char **envp);

#endif