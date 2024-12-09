/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_execution.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-hoo <svan-hoo@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/08 18:47:52 by svan-hoo      #+#    #+#                 */
/*   Updated: 2024/12/05 17:05:40 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_path(char *command, char **envp)
{
	char	*path;
	char	**all_paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (ft_strjoin_d(".", command, '/'));
	all_paths = ft_split(envp[i] + 5, ':');
	if (all_paths == NULL)
		return (NULL);
	i = 0;
	while (all_paths[i] != NULL)
	{
		path = ft_strjoin_d(all_paths[i], command, '/');
		if (path == NULL)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		ft_free_null(&path);
		i++;
	}
	ft_free_array(all_paths);
	return (path);
}

void	execute_sys_cmd(char **cmd_array, char **envp)
{
	int		exit_code;
	char	*path;

	if (cmd_array[0][0] == '/'
		|| cmd_array[0][0] == '.'
		|| cmd_array[0][0] == '~')
	{
		execve(cmd_array[0], cmd_array, envp);
		exit_code = errno;
	}
	else
	{
		path = find_path(cmd_array[0], envp);
		if (path == NULL && errno == ENOMEM)
			return ;
		if (path != NULL)
			execve(path, cmd_array, envp);
		exit_code = errno;
		if (access(cmd_array[0], X_OK) == -1)
			exit_code = 127;
	}
	errno = exit_code;
}

static void	export_loop(char **cmd_array, char ***envp, char ***envp_sorted)
{
	size_t	index;

	index = 0;
	while (cmd_array[++index])
	{
		errno = builtin_export(cmd_array[index], envp, envp_sorted);
		if (errno)
			break ;
	}
	if (index == 1 && !errno)
		print_export_list(*envp_sorted);
}

static void	unset_loop(char **cmd_array, char **envp, char **envp_sorted)
{
	size_t	index;

	index = 0;
	while (cmd_array[++index])
	{
		errno = builtin_unset(cmd_array[index], envp);
		if (!errno)
			errno = builtin_unset(cmd_array[index], envp_sorted);
		if (errno)
			break ;
	}
}

int	execute_builtin(t_shell *shell, char **cmd_array, char ***envp)
{
	errno = 0;
	if (!ft_strncmp(cmd_array[0], "cd", 3))
		errno = builtin_cd(cmd_array, envp, &shell->envp_sorted);
	else if (!ft_strncmp(cmd_array[0], "pwd", 4))
		errno = builtin_pwd();
	else if (!ft_strncmp(cmd_array[0], "env", 4))
		errno = builtin_env(*envp);
	else if (!ft_strncmp(cmd_array[0], "echo", 5))
		errno = builtin_echo(cmd_array);
	else if (!ft_strncmp(cmd_array[0], "exit", 5))
		errno = builtin_exit(shell, cmd_array);
	else if (!ft_strncmp(cmd_array[0], "unset", 6))
		unset_loop(cmd_array, *envp, shell->envp_sorted);
	else if (!ft_strncmp(cmd_array[0], "export", 7))
		export_loop(cmd_array, envp, &shell->envp_sorted);
	return (errno);
}
