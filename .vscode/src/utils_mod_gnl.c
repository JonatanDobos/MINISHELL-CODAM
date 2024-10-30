#include "../minishell.h"

static void	*free_line(char *line)
{
	if (line != NULL)
		free(line);
	return (NULL);
}

static size_t	nl_len(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i] && (i == 0 || str[i - 1] != '\n'))
			i++;
		return (i);
	}
	return (0);
}

static size_t	nl_check(char *str)
{
	while (str && *str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*get_buf(char *buf, char *line, size_t i, size_t j)
{
	const size_t	l_len = nl_len(line);
	const size_t	b_len = nl_len(buf);
	char			*new_line;
	char			*temp_line;

	if (b_len == 0)
		return (line);
	temp_line = line;
	new_line = (char *)malloc(l_len + b_len + 1);
	if (!new_line)
		return (free_line(line));
	while (i < l_len)
		new_line[i++] = *(temp_line++);
	while (j < b_len)
		new_line[i++] = buf[j++];
	new_line[i] = '\0';
	free_line(line);
	i = 0;
	while (buf[j])
		buf[i++] = buf[j++];
	buf[i] = '\0';
	return (new_line);
}

// On "\n" input it returns "\0" instead of NULL
// Does not return "\n" at the end
char	*get_next_line_heredoc(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		bytesread;
	char		*line;

	line = (char *)malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	line = get_buf(buffer, line, 0, 0);
	if (nl_check(line) != 0 || line == NULL)
		return (line);
	bytesread = BUFFER_SIZE;
	while (line && nl_check(line) == 0 && bytesread == BUFFER_SIZE)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (free_line(line));
		buffer[bytesread] = '\0';
		line = get_buf(buffer, line, 0, 0);
		if (!line)
			return (NULL);
	}
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}
