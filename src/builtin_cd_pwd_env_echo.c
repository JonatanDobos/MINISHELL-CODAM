#include "../minishell.h"

void	builtin_pwd(char **envp)
{
	errno = 0;
	printf("%s\n", get_env(envp, "PWD="));
}

void	builtin_cd(char *operand, char **envp, t_shell *shell)
{
	char		*path;
	int			ret;
	const char	*cwd = strdup(get_env(envp, "PWD="));

	errno = 0;
	cd_deslash(operand);
	if (operand == NULL || !ft_strncmp(operand, "~", 1))
		path = get_env(envp, "HOME=");
	else if (!ft_strncmp(operand, "-", 2))
		path = get_env(envp, "OLDPWD=");
	else
		path = ft_strjoin_d(ft_strdup(get_env(envp, "PWD=")), operand, '/');
	ret = chdir(path);
	if (ret == ERROR)
		cd_error(path);
	else
	{
		builtin_export(ft_strjoin("PWD=", path), shell);
		builtin_export(ft_strjoin("OLDPWD=", cwd), shell);
	}
	free((char *)cwd);
}

void	builtin_env(char **envp)
{
	int	i;

	errno = 0;
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

void	builtin_echo(char **cmd_array, char **envp)
{
	int	i;

	errno = 0;
	i = 1;
	while (cmd_array[i])
	{
		printf("%s", cmd_array[i]);
		if (cmd_array[++i])
			printf(" ");
	}
	printf("\n");
}
