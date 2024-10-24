#include "../minishell.h"

static pid_t	kiddo(t_shell *shell,
	t_token *token, int *standup, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (inp_outp_manager(shell, token, standup, pipe_fds))
			return (close(STDOUT_FILENO), exit_clean(shell, 0, NULL), pid);
		if (token->type == T_BUILTIN)
			execute_builtin(shell, token->cmd_array, &shell->envp);
		else
			execute_sys_cmd(token->cmd_array, shell->envp);
		close(STDOUT_FILENO);
		exit_clean(shell, errno, token->cmd_array[0]);
	}
	return (pid);
}

static int	zombie_prevention_protocol(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (errno);
	while (wait(NULL) != -1)
		;//check status, if ENOMEM do not wait for the others, escape while you still can
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (errno);
}

// DOES NOT WORK AT ALL
static int	exceptionweee_heredoc(t_shell *shell, t_token *token, int *standup)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
	{
		open_heredocs(shell, token->redirect, standup);
		exit_clean(shell, errno, NULL);
	}
	if (waitpid(pid, &status, 0) == -1)
		return (errno);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (errno);
}

static int
	exceptionweee(t_shell *shell, t_token *token, int *standup)
{
	int		status;

	errno = 0;
	if (check_for_heredoc(token->redirect) == true)
	{
		status = exceptionweee_heredoc(shell, token, standup);
		if (status)
			return (status);
	}
	open_files(shell, token->redirect);
	if (errno)
		status = EXIT_FAILURE;
	else
		status = execute_builtin(shell, token->cmd_array, &shell->envp);
	return (status);
}

int	execution(t_shell *shell)
{
	t_token	*token;
	pid_t	pid;
	int		pipe_fds[2];
	int		standup[2];

	standup[0] = dup(STDIN_FILENO);
	standup[1] = dup(STDOUT_FILENO);
	token = shell->token_head;
	if (token->next == NULL && token->type == T_BUILTIN)
		return (exceptionweee(shell, token, standup));
	while (token != NULL)
	{
		if (pipe(pipe_fds) == -1)
			exit_clean(shell, errno, "pipe()");
		pid = kiddo(shell, token, standup, pipe_fds);
		if (pid == -1)
			exit_clean(shell, errno, "fork()");
		set_input(shell, pipe_fds[0]);
		close(pipe_fds[1]);
		token = token->next;
	}
	set_input(shell, standup[0]);
	set_output(shell, standup[1]);
	return (zombie_prevention_protocol(pid));
}
