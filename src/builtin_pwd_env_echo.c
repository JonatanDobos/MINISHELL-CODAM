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
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	builtin_echo(char **cmd_array, char **envp)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = (cmd_array[1] && !ft_strncmp("-n", cmd_array[1], 3));
	if (n_flag)
		i = 2;
	while (cmd_array[i])
	{
		ft_putstr(cmd_array[i]);
		if (cmd_array[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!n_flag)
	{
		ft_putchar('\n');
	}
}
