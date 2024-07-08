#include "../minishell.h"

// RETURN: false = failure
bool	set_input(int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		return (false);
	if (close(input_fd) == -1)
		return (false);
	return (true);
}

// RETURN: false = failure
bool	set_output(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		return (false);
	if (close(output_fd) == -1)
		return (false);
	return (true);
}

// RETURN: -1 = failure
int	open_inputfile(const char *inputfile)
{
	int	fd;

	fd = open(inputfile, O_RDONLY);
	return (fd);
}

// RETURN: -1 = failure
int	open_outputfile(const char *outputfile)
{
	int	fd;

	fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}
