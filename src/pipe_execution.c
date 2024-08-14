#include "../minishell.h"

static char	*select_path(char *command, char **envp)
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
		error_exit(errno, command);
	i = 0;
	while (all_paths[i] != NULL)
	{
		path = ft_strjoin_d(all_paths[i], command, '/');
		if (path == NULL)
			error_exit(errno, command);
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
	char	*path;

	if (cmd_array[0][0] == '/'
		|| cmd_array[0][0] == '.'
		|| cmd_array[0][0] == '~')
	{
		execve(cmd_array[0], cmd_array, envp);
	}
	else
	{
		path = select_path(cmd_array[0], envp);
		if (path == NULL)
			error_exit(127, cmd_array[0]);
		execve(path, cmd_array, envp);
		if (access(cmd_array[0], X_OK) == -1)
			error_exit(127, cmd_array[0]);
	}
	error_exit(errno, cmd_array[0]);
}

int	execute_builtin(char **cmd_array, t_shell *shell)
{
	if (!ft_strncmp(cmd_array[0], "cd", 3))
		builtin_cd(cmd_array[1], shell->envp, shell);
	if (!ft_strncmp(cmd_array[0], "pwd", 4))
		builtin_pwd(shell->envp);
	if (!ft_strncmp(cmd_array[0], "env", 4))
		builtin_env(shell->envp);
	if (!ft_strncmp(cmd_array[0], "echo", 5))
		builtin_echo(cmd_array, shell->envp);
	if (!ft_strncmp(cmd_array[0], "unset", 6))
		builtin_unset(cmd_array, shell->envp);
	if (!ft_strncmp(cmd_array[0], "export", 7))
		builtin_export(cmd_array[1], shell);
	return (errno);
}
