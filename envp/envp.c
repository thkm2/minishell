/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:01:49 by kgiraud           #+#    #+#             */
/*   Updated: 2025/01/09 16:26:27 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init_envp(t_env **env, char **envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		printf("envp : %s\n", envp[i]);
		tmp = ft_split(envp[i], '=');
		if (!tmp)
		{
			perror("minishell: init env error");
			return ;
		}
		if (tmp[1])
			add_env_node(env, tmp[0], tmp[1]);
		else
			add_env_node(env, tmp[0], "");
		ft_free_split(tmp);
	}
}
