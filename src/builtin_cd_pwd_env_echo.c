#include "../minishell.h"

void	builtin_pwd(char **envp)
{
	printf("%s\n", get_env(envp, "PWD="));
	// exit success
}

void	builtin_cd(char **cmd_array, char **envp)
{
	const char	*path = cmd_array[1];
	int			ret;

	if (path == NULL)
		ret = chdir(get_env(envp, "HOME="));
	else if (strncmp(path, "-", 2))
		ret = chdir(get_env(envp, "OLDPWD="));
	else
		ret = chdir(path);
	if (ret != SUCCESS)
		return ; // exit with proper error msg
	// exit success
}

void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

void	builtin_echo(char **cmd_array, char **envp)
{
	int	i;

	i = 1;
	while (cmd_array[i])
	{
		printf("%s", cmd_array[i]);
		if (cmd_array[++i])
			printf(" ");
	}
	printf("\n");
}
