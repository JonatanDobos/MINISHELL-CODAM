#include "../minishell.h"

static int	cd_init_direction(char ***direction, char *operand)
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
		operand[i] = '\0';
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

static char	*cd_create_path(char *path, char *operand)
{
	char	**direction;
	int		i;

	if (path == NULL)
		return (NULL);
	if (cd_init_direction(&direction, operand) == ERROR)
		return (NULL);
	i = 0;
	while (direction[i] != NULL)
	{
		path = cd_append_direction(path, direction[i]);
		if (path == NULL)
			return (NULL);
		++i;
	}
	ft_free_array(direction);
	return (path);
}

static void	cd_print_error(char *operand)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (operand == NULL || !ft_strncmp(operand, "~", 2))
	{
		ft_putendl_fd("HOME not set", STDERR_FILENO);
		return ;
	}
	if (!ft_strncmp(operand, "-", 2))
	{
		ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
		return ;
	}
	else
		ft_putstr_fd(operand, STDERR_FILENO);
	if (access(operand, F_OK) == ERROR)
		ft_putendl_fd(": no such file or directory", STDERR_FILENO);
	else if (access(operand, R_OK) == ERROR)
		ft_putendl_fd(": permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": not a directory", STDERR_FILENO);
}

void	builtin_cd(char *operand, char ***envp)
{
	const char	*cwd = getcwd(NULL, 0);
	char		*path;
	int			ret;

	if (operand == NULL || !ft_strncmp(operand, "~", 2))
		path = ft_strdup(get_env(*envp, "HOME="));
	else if (!ft_strncmp(operand, "-", 2))
	{
		printf("%s\n", get_env(*envp, "OLDPWD="));
		path = ft_strdup(get_env(*envp, "OLDPWD="));
	}
	else
		path = cd_create_path(ft_strdup(cwd), operand);
	if (path == NULL)
		return ;
	ret = chdir(path);
	if (ret == ERROR)
		cd_print_error(operand);
	else
	{
		*envp = builtin_export(ft_strjoin("PWD=", path), *envp);
		*envp = builtin_export(ft_strjoin("OLDPWD=", cwd), *envp);
	}
	free((char *)cwd);
	free(path);
}
