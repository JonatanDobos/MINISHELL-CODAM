#include "../minishell.h"

void	builtin_pwd(t_shell *shell)
{
	printf("%s\n", get_env(shell->envp, "PWD="));
	// exit success
}

void	builtin_cd(t_shell *shell, char **cmd)
{
	const char	*path = cmd[1];
	int			ret;

	if (path == NULL)
		ret = chdir(get_env(shell->envp, "HOME="));
	else if (strncmp(path, "-", 2))
		ret = chdir(get_env(shell->envp, "OLDPWD="));
	else
		ret = chdir(path);
	if (ret != SUCCESS)
		return ; // exit with proper error msg
	// exit success
}

void	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
		printf("%s\n", shell->envp[i++]);
}

void	builtin_echo(t_shell *shell, char **cmd_array)
{
	int	i;

	i = 1;
	while (cmd_array[i])
	{
		printf("%s", cmd_array[i]);
		if (cmd_array[++i])
			write(STDOUT_FILENO, " ", 1);
	}
	printf("\n");
}
