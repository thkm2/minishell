/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:09:47 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/08 15:49:08 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_echo(char **av);
void	ft_pwd(void);

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s", envp[i]);
		ft_printf("\n");
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
	char *line;

	(void)ac;
	(void)av;
	line = readline(PROMPT);
	while(ft_strncmp(line, "exit", 4))
	{
		if (*line)
		{
			if (ft_strncmp(line, "env", 4) == 0)
			{
				ft_printf("builtin env\n");
				ft_env(envp);
			}
			else if (ft_strncmp(line, "echo", 4) == 0)
			{
				ft_printf("builtin echo\n");
				ft_echo(ft_split(line, ' '));
			}
			else if (ft_strncmp(line, "pwd", 3) == 0)
			{
				//ft_printf("builtin pwd\n");
				ft_pwd();
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