#include "../minishell.h"

bool	export_sorted_syntax(char *envar)
{
	int	i;

	if (envar == NULL || !envar[0])
		return (false);
	i = 0;
	if (!ft_isalpha(envar[i]) && envar[i] != '_')
		return (false);
	++i;
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (false);
		++i;
	}
	return (true);
}

void	ptr_switch(char **src_index, char **dest_index)
{
	char	*tmp;

	if (!src_index || !dest_index)
		return ;
	tmp = *dest_index;
	*dest_index = *src_index;
	*src_index = tmp;
}

// Only use when '=' is present! otherwise use ft_strdup()
char	*strdup_export_format(const char *str)
{
	const size_t	len = ft_strlen(str);
	char			*new_str;
	size_t			i;
	size_t			j;

	if (!str || !len)
		return (NULL);
	if (!ft_strchr(str, '='))
		return (ft_strdup(str));
	new_str = (char *)malloc(sizeof(char) * (len + 3));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '=')
		new_str[j++] = str[i++];
	new_str[j++] = str[i++];
	new_str[j++] = '\"';
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j++] = '\"';
	new_str[j] = '\0';
	return (new_str);
}

short	cmp_export_sort(char *relevant, char *compared_to)
{
	size_t	i;

	i = 0;
	while (relevant[i] && relevant[i] == compared_to[i]
		&& relevant[i] != '=' && compared_to[i] != '=')
		i++;
	if ((relevant[i] == '=' || relevant[i] == '\0')
		&& (compared_to[i] == '=' || compared_to[i] == '\0'))
		return (0);
	if ((compared_to[i] == '=' || compared_to[i] == '\0')
		|| (ft_islower(relevant[i]) && ft_isupper(compared_to[i]))
		|| (!ft_isalpha(relevant[i]) && ft_isupper(compared_to[i])
			&& relevant[i] != '=')
		|| (!ft_isalpha(compared_to[i]) && ft_islower(relevant[i])))
		return (1);
	if ((relevant[i] == '=' || relevant[i] == '\0')
		|| (ft_isupper(relevant[i]) && ft_islower(compared_to[i]))
		|| (ft_isupper(relevant[i]) && !ft_isalpha(compared_to[i]))
		|| (ft_islower(compared_to[i]) && !ft_isalpha(relevant[i])))
		return (-1);
	return (relevant[i] - compared_to[i]);
}

int	envp_key_index(char **envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (key[j] && envp[i][j] == key[j])
			++j;
		if ((!key[j] && (envp[i][j] == '=' || envp[i][j] == '\0'))
			|| (key[j] == '=' && envp[i][j] == '\0'))
			break ;
		i++;
	}
	return (i);
}
