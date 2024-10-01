#include "../minishell.h"

int	set_input(int input_fd)
{
	if (input_fd < 0)
		return (FAILURE);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (ERROR);
	if (close(input_fd) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	set_output(int output_fd)
{
	if (output_fd < 0)
		return (FAILURE);
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (ERROR);
	if (close(output_fd) == -1)
		return (ERROR);
	return (SUCCESS);
}

void	set_infile(t_shell *shell, char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		exit_clean(shell, errno, "open_infile()");
	if (set_input(fd) == ERROR)
		exit_clean(shell, errno, "set_input()");
}

void	set_outfile_append(t_shell *shell, char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		exit_clean(shell, errno, "open_outfile()");
	if (set_output(fd) == ERROR)
		exit_clean(shell, errno, "set_output()");
}

void	set_outfile_trunc(t_shell *shell, char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		exit_clean(shell, errno, "open_outfile()");
	if (set_output(fd) == ERROR)
		exit_clean(shell, errno, "set_output()");
}
