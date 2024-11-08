/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:47:31 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:47:32 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_envp(char **envp)
{
	char	**array;
	int		i;
	int		len;

	i = 0;
	while (envp[i] != NULL)
		++i;
	len = i;
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = ft_strdup(envp[i]);
		if (array[i] == NULL)
			return (ft_free_array(array), NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}
