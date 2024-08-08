/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:17 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/08/08 18:25:59 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(t_shell *shell, char **cmd)
{
	char	*path;
	int		ret;

	if (!cmd)
		return ;
	path = cmd[1];
	if (path == NULL)
		ret = chdir(get_envalue("HOME"));
	else if (strncmp(path, "-", 2))
		ret = chdir(get_envalue("OLDPWD"));
	else
		ret = chdir(path);
	if (ret != SUCCESS)
		return ; // exit with proper error msg
	// exit success
}
