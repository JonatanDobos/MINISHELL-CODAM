#include "../minishell.h"

// *str > string to read from
// start > starting index for reading from str
// end > stopping index, isn't included!
// Read part gets strdupped, return is malloced!
char	*strdup_index(char *str, size_t	start, size_t end)
{
	char	*ret;
	int		i;

	if (!str || start < 0 || end > ft_strlen(str) || end <= start)
		return (NULL);
	ret = (char *)malloc((end + 1 - start) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (start < end)
		ret[i++] = str[start++];
	ret[i] = '\0';
	return (ret);
}
