#include "../minishell.h"

void	syntax_error(void)
{
	write(STDERR_FILENO, "Syntax Error\n", 14);
}

void	cd_error(char *path)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (access(path, F_OK) == ERROR)
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
	else if (access(path, R_OK) == ERROR)
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
	else
		ft_putstr_fd("not a directory: ", STDERR_FILENO);
	if (path == NULL)
		ft_putendl_fd(" ", STDERR_FILENO);
	else
		ft_putendl_fd(path, STDERR_FILENO);
}

void	cd_deslash(char *operand)
{
	int	i;

	if (!operand)
		return ;
	i = 0;
	while (operand[i])
		++i;
	--i;
	if (operand[i] == '/')
		operand[i] = '\0';
}

int	export_syntax(const char *envar)
{
	int		i;

	if (envar == NULL)
		return (false);
	i = 0;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalpha(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	if (ft_strchr(envar, '=') <= envar)
		return (false);
	return (true);
}

char	*get_env(char **envp, const char *key)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		++i;
	ret = envp[i];
	if (ret != NULL)
		while (*ret++ != '=')
			;
	return (ret);
}
