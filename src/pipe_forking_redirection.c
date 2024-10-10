#include "../minishell.h"

static void	determine_output(t_shell *shell,
	t_list *next, int *standup, int *pipe_fds)
{
	if (next == NULL)
	{
		set_output(shell, standup[1]);
		if (close(pipe_fds[1]) == -1)
			exit_clean(shell, errno, "set_output()");
	}
	else
	{
		set_output(shell, pipe_fds[1]);
		if (close(standup[1]) == -1)
			exit_clean(shell, errno, "set_output()");
	}
}

void	open_files(t_shell *shell, t_token *token) // << heredoc
{
	int	i;

	i = 0;
	while (token->redirect[i])
	{
		if (!ft_strncmp(token->redirect[i], "<<", 2))
			here_doc(shell, \
			token->redirect[i] + skip_redir_whitespace(token->redirect[i]));
		else if (!ft_strncmp(token->redirect[i], "<", 1))
			set_infile(shell, \
			token->redirect[i] + skip_redir_whitespace(token->redirect[i]));
		else if (!ft_strncmp(token->redirect[i], ">>", 2))
			set_outfile_append(shell, \
			token->redirect[i] + skip_redir_whitespace(token->redirect[i]));
		else if (!ft_strncmp(token->redirect[i], ">", 1))
			set_outfile_trunc(shell, \
			token->redirect[i] + skip_redir_whitespace(token->redirect[i]));
		i++;
	}
}

static pid_t	kiddo(t_shell *shell,
	t_token *token, int *standup, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(standup[0]);
		close(pipe_fds[0]);
		determine_output(shell, token->next, standup, pipe_fds);
		if (token->redirect)
			open_files(shell, token);
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

static int
	exceptionweee(t_shell *shell, t_token *token, int *standup)
{
	int	status;
	if (token->redirect)
		open_files(shell, token);
	status = execute_builtin(shell, token->cmd_array, &shell->envp);
	set_input(shell, standup[0]);
	set_output(shell, standup[1]);
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
	{
		return (exceptionweee(shell, token, standup));
	}
	while (token != NULL)
	{
		if (pipe(pipe_fds) == -1)
			exit_clean(shell, errno, "pipe()");
		pid = kiddo(shell, token, standup, pipe_fds);
		set_input(shell, pipe_fds[0]);
		close(pipe_fds[1]);
		token = token->next;
	}
	set_input(shell, standup[0]);
	set_output(shell, standup[1]);
	return (zombie_prevention_protocol(pid));
}
