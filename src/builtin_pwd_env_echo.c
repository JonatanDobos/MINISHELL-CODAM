#include "../minishell.h"

void	builtin_pwd(char **envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return ;
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
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
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (cmd_array[i] && !ft_strncmp("-n", cmd_array[i], 3))
	{
		n_flag = true;
		++i;
	}
	while (cmd_array[i])
	{
		printf("%s", cmd_array[i]);
		if (cmd_array[++i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}
