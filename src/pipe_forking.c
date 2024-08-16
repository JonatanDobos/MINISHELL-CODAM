#include "../minishell.h"

static void	ft_close(int fd, char *id)
{
	char	buffer[100];

	if (close(fd) == -1)
		fprintf(stderr, "%s:\t\e[31mfailed to close [%d]\e[0m\n", id ,fd);
	else
		fprintf(stderr, "%s:\t\e[34mclosed [%d]\e[0m\n", id ,fd);
}

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

void	open_files(t_shell *shell, t_token *token) // << heredoc, >> append
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

static pid_t	kiddo(t_shell *shell, t_token *token, int *standup, int *pipe_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_close(pipe_fds[0], token->cmd_array[0]);
		if (token->next == NULL)
		{
			if (set_output(standup[1]) == ERROR)
				exit_clean(shell, errno, "set_output()");
			ft_close(pipe_fds[1], token->cmd_array[0]);
		}
		else
		{
			if (set_output(pipe_fds[1]) == ERROR)
				exit_clean(shell, errno, "set_output()");
			else
				fprintf(stderr, "%s:\t\e[33mswapd [\e[34m%d\e[33m, 1]\e[0m\n", token->cmd_array[0], pipe_fds[1]);
			ft_close(standup[1], token->cmd_array[0]);
		}
		ft_close(standup[0], token->cmd_array[0]);
		// if (token->redirect)
		// 	open_files(shell, token); // doesn't work because parsing is incomplete
		if (token->type == T_BUILTIN)
			execute_builtin(token->cmd_array, &shell->envp);
		else
			execute_sys_cmd(token->cmd_array, shell->envp);
		ft_close(STDOUT_FILENO, token->cmd_array[0]);
		exit_clean(shell, errno, token->cmd_array[0]);
	}
	return (pid);
}

static int	zombie_prevention_protocol(int pid)
{
	int	status;

	printf("\e[35mParent:\tlooking for pid...\e[0m\n");
	if (waitpid(pid, &status, 0) == -1)
		return (errno);
	printf("\e[35mParent:\tpid found\e[0m\n");
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
	printf("Parent:\t\e[32mduped: [%d, %d]\e[0m\n", standup[0], standup[1]);
	token = shell->token_head;
	if (token->next == NULL && token->type == T_BUILTIN)
		return (execute_builtin(token->cmd_array, &shell->envp)); // doesn't include redirects yet
	while (token != NULL)
	{
		if (pipe(pipe_fds) == -1)
			exit_clean(shell, errno, "pipe()");
		printf("Parent:\t\e[32mpiped: [%d, %d]\e[0m\n", pipe_fds[0], pipe_fds[1]);
		pid = kiddo(shell, token, standup, pipe_fds);
		if (set_input(pipe_fds[0]) == ERROR)
			exit_clean(shell, errno, "set_input()");
		else
			printf("Parent:\t\e[33mswapd [\e[34m%d\e[33m, 0]\e[0m\n", pipe_fds[0]);
		ft_close(pipe_fds[1], "Parent");
		token = token->next;
	}
	set_input(standup[0]);
	set_output(standup[1]);
	return (zombie_prevention_protocol(pid));
}
