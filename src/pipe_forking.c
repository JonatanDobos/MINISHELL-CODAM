#include "../minishell.h"

void	infile(t_shell *shell, char *infile)
{
	int	fd;

	fd = open_infile(infile);
	if (fd == -1)
		exit_clean(shell, errno, "open_infile()");
	if (set_input(fd) == ERROR)
		exit_clean(shell, errno, "set_input()");
}

void	outfile(t_shell *shell, char *outfile)
{
	int	fd;

	fd = open_outfile(outfile);
	if (fd == -1)
		exit_clean(shell, errno, "open_outfile()");
	if (set_output(fd) == ERROR)
		exit_clean(shell, errno, "set_output()");
}

void	open_files(t_shell *shell, t_token *token)
{
	int	i;

	i = 0;
	while (token->redirect[i])
	{
		// if (!ft_strncmp(token->cmd_array[i], "<<", 2))
		// 	heredoc(shell, token->cmd_array[i]);
		if (!ft_strncmp(token->cmd_array[i], "<", 1)) // else if
			infile(shell, token->cmd_array[i]);
		if (!ft_strncmp(token->cmd_array[i], ">", 1))
			outfile(shell, token->cmd_array[i]);
		i++;
	}
}

int	kiddo(t_shell *shell, t_token *token, int *standup, int *pipe_fds)
{
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		exit_clean(shell, errno, "pipe()");
	if (set_input(pipe_fds[0]) == ERROR)
		exit_clean(shell, errno, "set_input()");
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fds[0]);
		if (token->next == NULL){
			if (set_output(standup[1]) == ERROR)
				exit_clean(shell, errno, "set_output()");
		}
		else if (set_output(pipe_fds[1]) == ERROR)
				exit_clean(shell, errno, "set_output()");
		if (token->redirect)
			open_files(shell, token);
		if (token->type == T_BUILTIN)
			execute_builtin(token->cmd_array, shell);
		else
			execute_builtin(token->cmd_array, shell); // change to sys_cmd (currently has zombie/wait issue)
	}
	close(pipe_fds[1]);
	return (pid);
}

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

int	execution(t_shell *shell)
{
	t_token	*token;
	pid_t	pid;
	int		pipe_fds[2];
	int		standup[2];

	standup[0] = dup(STDIN_FILENO);
	standup[1] = dup(STDOUT_FILENO);
	token = shell->token_head;
	while (token != NULL)
	{
		pid = kiddo(shell, token, standup, pipe_fds);
		token = token->next;
	}
	dup2(standup[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(standup[0]);
	close(standup[1]);
	return (zombie_prevention_protocol(pid));
}
