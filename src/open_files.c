#include "../minishell.h"

static void	check_infile(char *infile)
{
	if (access(infile, R_OK))
	{
		syntax_error(errno, infile);
		errno = 2;
	}
}

static void	open_others(t_shell *shell, char **redir, bool has_heredoc)
{
	int	i;

	i = 0;
	while (redir[i] && !errno)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
		{
			++i;
			continue ;
		}
		if (!ft_strncmp(redir[i], "<", 1)){
			if (has_heredoc)
				check_infile(redir[i] + skip_redir_ws(redir[i]));
			else
				set_infile(shell, redir[i] + skip_redir_ws(redir[i]));}
		else if (!ft_strncmp(redir[i], ">>", 2))
			set_outfile_append(shell, redir[i] + skip_redir_ws(redir[i]));
		else if (!ft_strncmp(redir[i], ">", 1))
			set_outfile_trunc(shell, redir[i] + skip_redir_ws(redir[i]));
		++i;
	}
}

static pid_t heredoc_forking(t_shell *shell, char **redir)
{
	pid_t pid;
	int here_pipe[2];
	int prev_pipe = -1;
	int i = 0;

	while (redir[i])
	{
		if (!ft_strncmp(redir[i], "<<", 2))
		{
			// Create a pipe for each heredoc
			if (pipe(here_pipe) == -1) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}

			// Fork a process to handle the heredoc
			pid = fork();
			if (pid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0) {
				// Child process writes to heredoc pipe
				close(here_pipe[0]); // Close read end in child

				// Call heredoc to write data to pipe
				if (here_doc(shell, redir[i] + skip_redir_ws(redir[i]), here_pipe[1]) == EXIT_FAILURE)
					exit_clean(shell, errno, redir[i]);

				close(here_pipe[1]); // Close write end after writing
				close(STDOUT_FILENO);
				exit_clean(shell, errno, "here_doc child");
			}
			else {
				// Parent process: Manage pipes and save last pipe read end
				if (prev_pipe != -1)
					close(prev_pipe); // Close previous pipe read end if exists

				close(here_pipe[1]); // Close write end in parent
				prev_pipe = here_pipe[0]; // Save current read end for input
			}
		}
		i++;
	}
//
			char *check = get_next_line(here_pipe[0]);
			fprintf(stderr, "\ntotal heredoc output: %s\n", check);
			free(check);
//
	// Set last heredoc's read end as input for the parent process
	set_input(shell, prev_pipe);
	return pid;
}

int	open_files(t_shell *shell, char **redir)
{
	pid_t	pid;
	bool	has_heredoc;
	int		i;

	if (redir == NULL)
		return (EXIT_SUCCESS);
	errno = 0;
	has_heredoc = false;
	i = 0;
	while (redir[i] && has_heredoc == false)
	{
		if (!ft_strncmp(redir[i], "<<", 2))
			has_heredoc = true;
		++i;
	}
	if (has_heredoc)
	{
		pid = heredoc_forking(shell, redir);
		open_others(shell, redir, has_heredoc);
		return (zombie_prevention_protocol(pid));
	}
	open_others(shell, redir, has_heredoc);
	return (errno);
}
