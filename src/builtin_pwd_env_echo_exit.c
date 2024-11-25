/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd_env_echo_exit.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:46:08 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/11/25 18:12:22 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (errno);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}

int	builtin_env(char **envp)
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

int	builtin_echo(char **cmd_array)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = echo_n_flag_check(cmd_array[1]);
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

int	builtin_exit(t_shell *shell, char **cmd_array)
{
	size_t	i;

	if (cmd_array[1])
	{
		if (cmd_array[2])
			return (ft_putstr_fd("minishell: exit: too many arguments\n", \
					STDERR_FILENO), EXIT_FAILURE);
		i = 0;
		while (cmd_array[1][i])
		{
			if (!ft_isdigit(cmd_array[1][i]) && cmd_array[1][i] != '"'
			&& cmd_array[1][i] != '+' && cmd_array[1][i] != '-')
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n",
					STDERR_FILENO);
				return (2);
			}
			i++;
		}
		printf("exit\n");
		exit_clean(shell, (unsigned char)ft_atoi(cmd_array[1]), NULL);
	}
	exit_clean(shell, errno, NULL);
	return (38);
}
