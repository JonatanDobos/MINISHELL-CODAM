/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:46:06 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/11/08 18:46:07 by svan-hoo         ###   ########.fr       */
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
	else if (ft_strncmp(direction, "..", 3) == 0)
	{
		tmp = ft_strrchr(path, '/');
		if (tmp)
			*tmp = '\0';
	}
	else
	{
		tmp = path;
		path = ft_strjoin_d(path, direction, '/');
		if (path == NULL)
			return (NULL);
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
	if (operand == NULL || !ft_strncmp(operand, "~", 2))
		return (ft_strdup(get_env(envp, "HOME=")));
	else if (!ft_strncmp(operand, "-", 2))
	{
		printf("%s\n", get_env(envp, "OLDPWD="));
		return (ft_strdup(get_env(envp, "OLDPWD=")));
	}
	if (*operand == '/')
		return (path);
	if (cd_init_direction(&direction, operand) == ERROR)
		return (NULL);
	i = 0;
	while (direction[i] != NULL)
	{
		path = cd_append_direction(path, direction[i++]);
		if (path == NULL)
			return (NULL);
	}
	ft_free_array(direction);
	return (path);
}

static int	cd_print_error(const char *operand)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (operand == NULL || !ft_strncmp(operand, "~", 2))
	{
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	}
	if (!ft_strncmp(operand, "-", 2))
	{
		ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(operand, STDERR_FILENO);
		if (access(operand, F_OK) == ERROR)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else if (access(operand, R_OK) == ERROR)
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else if (access(operand, X_OK) == ERROR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **cmd_array, char ***envp, char ***envp_sorted)
{
	const char	*operand = cmd_array[1];
	const char	*cwd = getcwd(NULL, 0);
	char		*path;
	int			exit_code;

	if (cmd_array[1] && cmd_array[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit_code = EXIT_SUCCESS;
	path = cd_create_path(ft_strdup(cwd), operand, *envp);
	if (path == NULL)
		exit_code = errno;
	if (chdir(path) == ERROR && ft_strncmp(path, cwd, ft_strlen(path)))
		exit_code = cd_print_error(operand);
	else
	{
		builtin_export(ft_strjoin("PWD=", path), envp, envp_sorted);
		builtin_export(ft_strjoin("OLDPWD=", cwd), envp, envp_sorted);
	}
	free((char *)cwd);
	free(path);
	return (exit_code);
}
