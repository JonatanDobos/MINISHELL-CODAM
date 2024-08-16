#include "../minishell.h"

// static void	ft_close(int fd, char *id)
// {
// 	if (close(fd) == -1)
// 		fprintf(stderr, "%s:\t\e[31mfailed to close [%d]\e[0m\n", id ,fd);
// 	else
// 		fprintf(stderr, "%s:\t\e[34mclosed [%d]\e[0m\n", id ,fd);
// }

void	infile(t_shell *shell, char *infile)
{
	int	fd;

	fd = open_infile(infile);
	if (fd == -1)
		exit_clean(shell, errno, "open_infile()");
	if (set_input(fd) == ERROR)
		exit_clean(shell, errno, "set_input()");
}

void	outfile_append(t_shell *shell, char *outfile)
{
	int	fd;

	fd = open_outfile(outfile);
	if (fd == -1)
		exit_clean(shell, errno, "open_outfile()");
	if (set_output(fd) == ERROR)
		exit_clean(shell, errno, "set_output()");
}

void	outfile_trunc(t_shell *shell, char *outfile)
{
	int	fd;

	fd = open_outfile(outfile);
	if (fd == -1)
		exit_clean(shell, errno, "open_outfile()");
	if (set_output(fd) == ERROR)
		exit_clean(shell, errno, "set_output()");
}

void	open_files(t_shell *shell, t_token *token) // << heredoc, >> append
{
	int	i;

	i = 0;
	while (token->redirect[i])
	{
		/*if (!ft_strncmp(token->cmd_array[i], "<<", 2))
		 	heredoc(shell, token->cmd_array[i]);
		else */if (!ft_strncmp(token->cmd_array[i], "<", 1))
			infile(shell, token->cmd_array[i]);
		/*if (!ft_strncmp(token->cmd_array[i], ">>", 1))
			outfile_append(shell, token->cmd_array[i]);
		else */if (!ft_strncmp(token->cmd_array[i], ">", 1))
			outfile_trunc(shell, token->cmd_array[i]);
		i++;
	}
}

static pid_t	kiddo(t_shell *shell, t_token *token, int *standup, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(standup[0]);
		close(pipe_fds[0]);
		if (token->next == NULL)
		{
			if (set_output(standup[1]) == ERROR
				|| close(pipe_fds[1]) == -1)
				exit_clean(shell, errno, "set_output()");
		}
		else
		{
			if (set_output(pipe_fds[1]) == ERROR
				|| close(standup[1]))
				exit_clean(shell, errno, "set_output()");
		}
		if (token->redirect)
			open_files(shell, token); // doesn't work because parsing is incomplete
		if (token->type == T_BUILTIN)
			execute_builtin(token->cmd_array, &shell->envp);
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

	// printf("\e[35mParent:\tlooking for pid...\e[0m\n");
	if (waitpid(pid, &status, 0) == -1)
		return (errno);
	// printf("\e[35mParent:\tpid found\e[0m\n");
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
	if (token->next == NULL && token->type == T_BUILTIN)
		return (execute_builtin(token->cmd_array, &shell->envp)); // doesn't include redirects yet
	while (token != NULL)
	{
		if (pipe(pipe_fds) == -1)
			exit_clean(shell, errno, "pipe()");
		pid = kiddo(shell, token, standup, pipe_fds);
		if (set_input(pipe_fds[0]) == ERROR)
			exit_clean(shell, errno, "set_input()");
		close(pipe_fds[1]);
		token = token->next;
	}
	set_input(standup[0]);
	set_output(standup[1]);
	return (zombie_prevention_protocol(pid));
}
