/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:46:06 by svan-hoo          #+#    #+#             */
/*   Updated: 2025/01/06 18:32:34 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_init_direction(char ***direction, const char *operand)
{
	int	i;

	if (!operand)
		return (ERROR);
	i = 0;
	while (operand[i])
		++i;
	if (i)
		--i;
	if (operand[i] == '/')
		((char *)operand)[i] = '\0';
	*direction = ft_split(operand, '/');
	if (*direction == NULL)
		return (ERROR);
	return (SUCCESS);
}

static char	*cd_append_direction(char *path, char *direction)
{
	char	*tmp;

	if (ft_strncmp(direction, ".", 2) == 0)
		;
	else if (path && ft_strncmp(direction, "..", 3) == 0)
	{
		tmp = ft_strrchr(path, '/');
		if (tmp)
			*tmp = '\0';
	}
	else if (path)
	{
		tmp = path;
		path = ft_strjoin_d(path, direction, '/');
		if (path == NULL)
			return (free(tmp), NULL);
		free(tmp);
	}
	return (path);
}

static char	*cd_create_path(char *path, const char *operand, char **envp)
{
	char	**direction;
	int		i;

	if (path == NULL)
		return (NULL);
	if (operand == NULL || *operand == '\0' || !ft_strncmp(operand, "~", 2))
		return (free(path), ft_strdup(get_env(envp, "HOME=")));
	else if (!ft_strncmp(operand, "-", 2))
		return (free(path), printf("%s\n", get_env(envp, "OLDPWD=")),
			ft_strdup(get_env(envp, "OLDPWD=")));
	if (operand[0] == '~')
		return (free(path), cd_home_append(get_env(envp, "HOME="), operand));
	if (operand[0] == '/')
		return (free(path), ft_strdup((char *)operand));
	if (cd_init_direction(&direction, operand) == ERROR)
		return (free(path), NULL);
	i = 0;
	while (direction[i] != NULL)
	{
		path = cd_append_direction(path, direction[i++]);
		if (path == NULL)
			return (ft_free_array(direction), NULL);
	}
	return (ft_free_array(direction), path);
}

static int	cd_print_error(const char *path, const char *operand)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (path == NULL || !ft_strncmp(path, "~", 2))
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	if (!ft_strncmp(path, "-", 2))
		ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
	else
	{
		if (operand && operand[0] == '~' && operand[1] == '/')
			ft_putstr_fd(path, STDERR_FILENO);
		else if (operand)
			ft_putstr_fd(operand, STDERR_FILENO);
		if (access(path, F_OK) == ERROR)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (access(path, R_OK) == ERROR)
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else if (access(path, X_OK) == ERROR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	builtin_cd(char **cmd_array, char ***envp, char ***envp_sorted)
{
	const char	*operand;
	const char	*cwd = getcwd(NULL, 0);
	char		*path;
	int			exit_code;

	if (cwd == NULL)
		return (FAILURE);
	if (!cd_set_operand(cmd_array, (char **)(&operand)))
		return (ft_putstr_fd("minishell: cd: too many arguments\n", \
		STDERR_FILENO), FAILURE);
	exit_code = SUCCESS;
	path = cd_create_path(ft_strdup(cwd), operand, *envp);
	if (path == NULL)
		exit_code = errno;
	if (exit_code == ENOMEM)
		return (free((char *)cwd), FAILURE);
	if (chdir(path) == ERROR && ft_strncmp(path, cwd, ft_strlen(path) + 1))
		exit_code = cd_print_error(path, operand);
	else
		exit_code = export_pwd(path, (char *)cwd, envp, envp_sorted);
	return (free((char *)cwd), free(path), exit_code);
}
