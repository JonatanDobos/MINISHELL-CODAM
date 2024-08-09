#include "../minishell.h"

static int	zombie_prevention_protocol(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (errno);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (errno);
}

int	first_kid(char *infile, t_token *token, char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (ERROR);
	set_output(pipe_fds[1]);
	pid = fork();
	if (pid == 0)
	{
		set_input(open_inputfile(infile));
		close(pipe_fds[0]);
		if (token->type == T_BUILTIN)
			execute_builtin(token->cmd_array, envp);
		else
			execute_sys_cmd(token->cmd_array, envp);
	}
	return (pipe_fds[0]);
}

int	middle_kid(int input_fd, t_token *token, char **envp)
{
	pid_t	pid;
	int		pipe_fds[2];

	set_input(input_fd);
	if (pipe(pipe_fds) == -1)
		return (ERROR);
	set_output(pipe_fds[1]);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[0]);
		if (token->type == T_BUILTIN)
			execute_builtin(token->cmd_array, envp);
		else
			execute_sys_cmd(token->cmd_array, envp);
	}
	return (pipe_fds[0]);
}

pid_t	last_kid(int input_fd, char *outfile, t_token *token, char **envp)
{
	pid_t	pid;

	set_input(input_fd);
	pid = fork();
	if (pid == 0)
	{
		set_output(open_outputfile(outfile));
		if (token->type == T_BUILTIN)
			execute_builtin(token->cmd_array, envp);
		else
			execute_sys_cmd(token->cmd_array, envp);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (pid);
}

int	execution(t_shell *shell)
{
	t_token	*token;
	int		input_fd;
	pid_t	pid;

	token = shell->token_head;
	input_fd = first_kid("Makefile", token, shell->envp);
	while (token != NULL && token->next != NULL)
	{
		// input_fd = token_directions(token);
		input_fd = middle_kid(input_fd, token, shell->envp);
		if (input_fd == ERROR)
			exit_clean(shell, errno, NULL);
		token = token->next;
	}
	pid = last_kid(input_fd, "outfile", token, shell->envp);
	if (pid == ERROR)
		exit_clean(shell, errno, NULL);
	return (zombie_prevention_protocol(pid));
}
