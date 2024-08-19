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

// RETURN: -1 = failure
int	open_infile(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	return (fd);
}

// RETURN: -1 = failure
int	open_outfile(const char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}
