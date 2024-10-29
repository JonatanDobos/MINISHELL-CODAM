#include "../minishell.h"

bool	close_all_fds(t_fds *fds)
{
	if (close_fd(&fds->pipe[0]) == -1)
		return (false);
	if (close_fd(&fds->pipe[1]) == -1)
		return (false);
	if (close_fd(&fds->stdup[0]) == -1)
		return (false);
	if (close_fd(&fds->stdup[1]) == -1)
		return (false);
	if (close(STDOUT_FILENO) == -1)
		return (false);
	return (true);
}

static pid_t	kiddo(t_shell *shell, t_token *token, t_fds *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		heredoc_fork(shell, token->redirect, fds, HERE_DOC);
		if (inp_outp_manager(shell, token, fds))
		{
			close_all_fds(fds);
			exit_clean(shell, EXIT_SUCCESS, NULL);
			return (pid);
		}
		if (token->type == T_BUILTIN)
			execute_builtin(shell, token->cmd_array, &shell->envp);
		else
			execute_sys_cmd(token->cmd_array, shell->envp);
		close_all_fds(fds);
		exit_clean(shell, errno, token->cmd_array[0]);
	}
	return (pid);
}

int	zombie_prevention_protocol(int pid)
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

static int
	exceptionweee(t_shell *shell, t_token *token, t_fds *fds)
{
	int	status;

	errno = 0;
	heredoc_fork(shell, token->redirect, fds, HERE_DUMMY);
	open_files(shell, token->redirect, check_for_heredoc(token->redirect));
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
	t_fds	fds;

	save_standard_fds(shell, fds.stdup);
	token = shell->token_head;
	if (token->next == NULL && token->type == T_BUILTIN)
		return (exceptionweee(shell, token, &fds));
	while (token != NULL)
	{
		if (pipe(fds.pipe) == -1)
			exit_clean(shell, errno, "pipe()");
		pid = kiddo(shell, token, &fds);
		if (pid == -1)
			exit_clean(shell, errno, "fork()");
		set_input(shell, fds.pipe[0]);
		close(fds.pipe[1]);
		token = token->next;
	}
	reset_fds(shell, fds.stdup);
	return (zombie_prevention_protocol(pid));
}
