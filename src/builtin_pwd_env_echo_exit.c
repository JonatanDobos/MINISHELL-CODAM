#include "../minishell.h"

int		builtin_pwd(char **envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (errno);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}

int		builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		builtin_echo(char **cmd_array, char **envp)
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
	return (EXIT_SUCCESS);
}

int		builtin_exit(t_shell *shell, char **cmd_array, char **envp)
{
	unsigned char	num;
	char			*code;
	size_t			i;

	code = cmd_array[1];// segfault bij enkel "exit", is dat de bedoeling?
	if (cmd_array[1] && cmd_array[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (code[i])
	{
		if (!ft_isdigit(code[i])
			&& code[i] != '"' && code[i] != '+' && code[i] != '-')
		{
			ft_putstr_fd("minishell: exit: numeric argument required",
				STDERR_FILENO);
			return (2);
		}
		i++;
	}
	num = (unsigned char)ft_atoi(code);
	exit_clean(shell, num, NULL);
	return (38);
}
