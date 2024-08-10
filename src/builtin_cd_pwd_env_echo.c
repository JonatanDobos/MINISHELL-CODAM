#include "../minishell.h"

void	builtin_pwd(char **envp)
{
	errno = 0;
	printf("%s\n", get_env(envp, "PWD="));
	exit(errno);
}

void	builtin_cd(char **cmd_array, char **envp)
{
	const char	*path = cmd_array[1];
	int			ret;

	errno = 0;
	if (path == NULL)
		ret = chdir(get_env(envp, "HOME="));
	else if (strncmp(path, "-", 2))
		ret = chdir(get_env(envp, "OLDPWD="));
	else
		ret = chdir(path);
	exit(errno);
}

void	builtin_env(char **envp)
{
	int	i;

	errno = 0;
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	exit(errno);
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
	exit(errno);
}
